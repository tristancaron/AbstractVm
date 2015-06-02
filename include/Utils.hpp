#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>

# include "EOperandType.hpp"

bool hasSuffix(const std::string &str, const std::string &suffix);
bool simpleMatcher(std::string &str, char &pattern);
bool hasPrefix(const std::string &str, const std::string &prefix);

std::string calculated(std::string const &a, std::string const &b,
        eOperandType type, std::string const &op);

int sIntCmp(std::string const &a, std::string const &b);
int sFloatCmp(std::string const &a, std::string const &b);

#endif