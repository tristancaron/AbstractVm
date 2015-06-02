#ifndef CORE_HPP
# define CORE_HPP

# include <iostream>
# include <vector>
# include <set>

# include "IOperand.hpp"
# include "FactoryOperand.hpp"

struct  s_info {
    std::string kind;
    std::string value;
};

class Core {
public:
    Core(void);
    Core(Core const &src);

    Core                            &operator=(Core const &src);

    void                            tokenizer(std::string &file, bool isFileName);
    void                            lexcialAnalyzer(void);
    void                            syntaxAnalyser(void);
    void                            executeCode(void);

    std::vector<std::string>        get_token(void) const;
    std::vector<s_info>             get_lexical(void) const;
    std::set<std::string>           get_instr(void) const;
    std::set<std::string>           get_values(void) const;
    std::vector<const IOperand*>    get_stack(void) const;
private:
    std::vector<std::string>        _token;
    std::vector<s_info>             _lexical;
    std::set<std::string>           _instr;
    std::set<std::string>           _values;
    std::vector<const IOperand*>    _stack;

    bool                            _isInstr(std::string token) const;
    bool                            _isValue(std::string token) const;
    void                            _push(std::string const &value);
    bool                            _assert(std::string const &value);
    std::string                     _extractValue(std::string const &value);
    eOperandType                    _extractOperand(std::string const &value);
    bool                            _pop(void);
    void                            _dump(void);
    void                            _print(void);
    void                            _doOperation(std::string opName);
    FactoryOperand                  _factoryOperand;
};

#endif