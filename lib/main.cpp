#include <sstream>

#include "Core.hpp"
#include "Utils.hpp"


static void     executeFile(std::string &file, bool isFile) {
    Core core;

    core.tokenizer(file, isFile);
    core.lexcialAnalyzer();
    core.syntaxAnalyser();
    core.executeCode();
}

static void     getCommand() {
    std::string         line;
    std::stringstream   result;
    std::string         final;

    while (std::getline(std::cin, line)) {
        if (hasSuffix(line, ";;")) {
            result << "exit";
            break;
        }
        result << line << std::endl;
    }
    final = result.str();
    executeFile(final, false);
}

int             main(int argc, char *argv[]) {
    std::string name;

    if (argc > 1) {
        name = std::string(argv[1]);
        if (!hasSuffix(name, ".avm")) {
            std::cerr << "Wrong file format :" << name << std::endl;
            return (-1);
        }
        executeFile(name, true);
    } else
        getCommand();
    return (0);
}