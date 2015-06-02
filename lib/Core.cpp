# include <exception>
# include <cstdlib>
# include <sstream>
# include <fstream>

#include "Core.hpp"
#include "EOperandType.hpp"
#include "Utils.hpp"

#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/numeric/conversion/cast.hpp"

Core::Core(void) {
    std::string instr[] = {
            "push",
            "pop",
            "dump",
            "assert",
            "add",
            "sub",
            "mul",
            "div",
            "mod",
            "print",
            "exit"
    };
    std::string values[] = {
            "int8(",
            "int16(",
            "int32(",
            "float(",
            "double("
    };


    _instr.insert(instr, instr + 11);
    _values.insert(values, values + 5);
}

Core::Core(Core const &src) {
    *this = src;
}

Core            &Core::operator=(Core const &src) {
    if (this != &src) {
        _token = src.get_token();
        _lexical = src.get_lexical();
        _instr = src.get_instr();
        _values = src.get_values();
        _stack = src.get_stack();
    }
    return *this;
}

void            Core::tokenizer(std::string &file, bool isFileName) {
    std::istream *code;
    if (isFileName) {
        code = new std::ifstream(file);
        if (!static_cast<std::ifstream*>(code)->is_open()) {
            std::cerr << "File doesn't exit." << std::endl;
            std::exit(1);
        }
    }
    else
        code = new std::istringstream(file);
    std::string     tmp;
    boost::regex    syntax("^(.*[^\\s])|()$");
    int             line(1);

    while (std::getline(*code, tmp)) {
        std::stringstream iss(tmp);
        if (!boost::regex_match(tmp, syntax)) {
            std::cerr << "Line " << line << " : \033[31mError\033[0m : "
                    << "Bad end of line" << std::endl;
            std::exit(1);
        }
        if (hasPrefix(tmp, "; ")) {
            _token.push_back(tmp);
        } else {
            while (std::getline(iss, tmp, ' '))
                _token.push_back(tmp);
        }
        ++line;
        _token.push_back("\\n");
    }
}

void            Core::lexcialAnalyzer(void) {
    int line(1);

    for (std::string token : _token) {
        if (_isInstr(token)) {
            _lexical.push_back(s_info());
            (_lexical.end() - 1)->kind = "INSTR";
            (_lexical.end() - 1)->value = token;
        } else if (_isValue(token)) {
            _lexical.push_back(s_info());
            (_lexical.end() - 1)->kind = "VALUE";
            (_lexical.end() - 1)->value = token;
        } else if (hasPrefix(token, "; ")) {
            _lexical.push_back(s_info());
            (_lexical.end() - 1)->kind = "COMMENT";
            (_lexical.end() - 1)->value = token;
        } else if (token == "\\n") {
            ++line;
            _lexical.push_back(s_info());
            (_lexical.end() - 1)->kind = "END_INSTR";
            (_lexical.end() - 1)->value = token;
        } else {
            std::cerr << "Unknows token \"" << token <<  "\" at line " << line
                    << ";" << std::endl;
            std::exit(1);
        }
    }
    _token.clear();
    _instr.clear();
    _values.clear();
}

bool            Core::_isInstr(std::string token) const {
    return _instr.find(token) != _instr.end();
}

bool            Core::_isValue(std::string token) const {
    for (auto value : _values) {
        if (hasPrefix(token, value) && hasSuffix(token, ")"))
            return (true);
    }
    return (false);
}

void            Core::syntaxAnalyser(void) {
    int     line(1);
    char    pattern;
    bool    hasExit(false);

    for (std::vector<s_info>::iterator it = _lexical.begin();
         it != _lexical.end(); ++it) {
        if (it->kind == "INSTR") {
            if (it->value == "push" || it->value == "assert") {
                ++it;
                if (it->kind == "VALUE") {
                    pattern = (hasPrefix(it->value, "int")) ? 'N' : 'Z';
                    if (!simpleMatcher(it->value, pattern)) {
                        std::cerr << "Line " << line << " : \033[31mError\033[0m : "
                                << "Invalid parameter in \"" << it->value
                                << "\"" << std::endl;
                        std::exit(1);
                    }
                    ++it;
                } else {
                    --it;
                    std::cerr << "Line " << line << " : \033[31mError\033[0m : "
                            << "Invalid use of \"" << it->value << "\""
                            << std::endl;
                    std::exit(1);
                }
            } else {
                if (!hasExit && it->value == "exit")
                    hasExit = true;
                ++it;
            }
        }
        if (it->kind != "END_INSTR" && it->kind != "COMMENT") {
            std::cerr << "Line " << line << " : \033[31mError\033[0m : "
                    << "Missing new line" << std::endl;
            std::exit(1);
        }
        ++line;
    }
    if (!hasExit) {
        std::cerr << "Line " << line << " : \033[31mError\033[0m : "
                << "Missing exit instruction" << std::endl;
        std::exit(1);
    }
}

void            Core::executeCode(void) {
    int line(1);

    for (std::vector<s_info>::iterator it = _lexical.begin();
         it != _lexical.end(); ++it) {
        if (it->value == "push") {
            ++it;
            try {
                _push(it->value);
            } catch (std::exception &e) {
                std::cerr << "Line " << line << " : " << e.what()
                        << " : Value don't fit" << std::endl;
                std::exit(1);
            }
        } else if (it->value == "pop") {
            if (!_pop()) {
                std::cerr << "Line " << line << " : \033[31mError\033[0m : Pop on empty stack"
                        << std::endl;
                std::exit(1);
            }
        } else if (it->value == "dump") {
            _dump();
        } else if (it->value == "assert") {
            ++it;
            if (!_assert(it->value)) {
                std::cerr << "Line " << line << " : \033[31mError\033[0m : Assert failed : "
                        << "\"assert " << it->value << "\""
                        << std::endl;
                std::exit(1);
            }
        } else if (it->value == "add"
                || it->value == "sub"
                || it->value == "mul"
                || it->value == "div"
                || it->value == "mod") {
            try {
                _doOperation(it->value);
            } catch (std::exception &e) {
                std::cerr << "Line " << line << " : \033[31m" << e.what()
                        << "\033[0m : " << it->value << " failed"
                        << std::endl;
                std::exit(1);
            }
        } else if (it->value == "print") {
            try {
                _print();
            } catch (std::exception &e) {
                std::cerr << "Line " << line << " : \033[31m" << e.what()
                        << "\033[0m : print failed"
                        << std::endl;
                std::exit(1);
            }
        } else if (it->kind == "END_INSTR") {
            ++line;
        }
    }
}

bool            Core::_assert(std::string const &value) {
    eOperandType    type = _extractOperand(value);
    std::string     val = _extractValue(value);

    return (_stack.back())->getType() == type
            && (_stack.back())->toString() == val;
}

void            Core::_push(std::string const &value) {
    eOperandType type = _extractOperand(value);

    try {
        IOperand const *tmp =
                _factoryOperand.createOperand(type, _extractValue(value));
        _stack.push_back(tmp);
    } catch (std::exception &e) {
        throw std::out_of_range(e.what());
    }
    return ;
}

eOperandType    Core::_extractOperand(std::string const &value) {
    if (hasPrefix(value, "int8")) {
        return (INT8);
    } else if (hasPrefix(value, "int16")) {
        return (INT16);
    } else if (hasPrefix(value, "int32")) {
        return (INT32);
    } else if (hasPrefix(value, "float")) {
        return (FLOAT);
    } else
        return (DOUBLE);
}

std::string     Core::_extractValue(std::string const &value) {
    size_t start(value.find("(") + 1);
    size_t length(value.length() - 1 - start);

    return (value.substr(start, length));
}

bool            Core::_pop(void) {
    if (!_stack.empty()) {
        delete _stack.back();
        _stack.pop_back();
        return (true);
    }
    return (false);
}

void            Core::_dump(void) {
    if (!_stack.empty()) {
        std::vector<const IOperand*>::iterator it = _stack.end() - 1;
        for (; it != _stack.begin(); --it)
            std::cout << (*it)->toString() << std::endl;
        std::cout << (*it)->toString() << std::endl;
    } else
        std::cout << "\033[36mInfo\033[0m : Dump on empty stack" << std::endl;
}

void            Core::_doOperation(std::string opName) {
    IOperand const *a;
    IOperand const *b;
    IOperand const *tmp;

    if (_stack.size() < 2)
        throw std::runtime_error("Stack Error");
    a = _stack.back();
    b = *(_stack.end() - 2);
    try {
        if (opName == "add")
            tmp = *a + *b;
        else if (opName == "sub")
            tmp = *a - *b;
        else if (opName == "mul")
            tmp = *a * *b;
        else if (opName == "div")
            tmp = *a / *b;
        else if (opName == "mod")
            tmp = *a % *b;
        else {
            throw std::runtime_error("");
        }
        delete _stack.back();
        _stack.pop_back();
        delete _stack.back();
        _stack.pop_back();
        _stack.push_back(tmp);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
    return ;
}

void            Core::_print(void) {
    int8_t v;

    if (_stack.size() < 1)
        throw std::runtime_error("Stack Error");
    if ((_stack.back())->getType() != INT8)
        throw std::runtime_error("Type Error");
    v = boost::numeric_cast<int8_t>(boost::lexical_cast<int>((_stack.back())->toString()));
    std::cout << boost::lexical_cast<std::string>(v) << std::endl;
    return ;
}

std::vector<std::string>        Core::get_token(void) const {
    return _token;
}

std::vector<s_info>             Core::get_lexical(void) const {
    return _lexical;
}

std::set<std::string>           Core::get_instr(void) const {
    return _instr;
}

std::set<std::string>           Core::get_values(void) const {
    return _values;
}

std::vector<const IOperand*>    Core::get_stack(void) const {
    return _stack;
}