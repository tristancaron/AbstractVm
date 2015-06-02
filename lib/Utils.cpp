#include "Utils.hpp"

#include "MyException.hpp"

#include <sstream>

#include "boost/regex.hpp"
#include "boost/lexical_cast.hpp"

bool hasSuffix(const std::string &str, const std::string &suffix) {
    return str.size() >= suffix.size() &&
            str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool hasPrefix(const std::string &str, const std::string &prefix) {
    return str.size() >= prefix.size() &&
            str.compare(0, prefix.size(), prefix) == 0;
}

bool simpleMatcher(std::string &str, char &pattern) {
    boost::regex n(".*\\({1}(-)?[0-9]+\\){1}");
    boost::regex z(".*\\({1}(-)?[0-9]+\\.{1}[0-9]+\\){1}");

    return boost::regex_match(str, ((pattern == 'N') ? n : z));
}

std::string calculated(std::string const &a, std::string const &b,
        eOperandType type, std::string const &op) {
    std::istringstream val1(a);
    std::istringstream val2(b);
    std::stringstream res;
    std::string       tmp;

    res.precision(500);
    if (type == INT8 || type == INT16 || type == INT32) {
        int64_t iVal1, iVal2, iRes;

        val1 >> iVal1;
        val2 >> iVal2;
        if (op == "add")
            iRes = iVal1 + iVal2;
        else if (op == "sub")
            iRes = iVal1 - iVal2;
        else if (op == "mul")
            iRes = iVal1 * iVal2;
        else if (op == "div") {
            if (iVal2 == 0) {
                throw MyException("Divide by zero");
            }
            iRes = iVal1 / iVal2;
        } else if (op == "mod") {
            if (iVal2 == 0) {
                throw MyException("Modulo by zero");
            }
            iRes = iVal1 % iVal2;
        } else {
            return "0";
        }
        res << std::fixed << iRes;
        tmp = res.str();
    } else {
        double dVal1, dVal2, dRes;

        val1 >> dVal1;
        val2 >> dVal2;
        if (op == "add")
            dRes = dVal1 + dVal2;
        else if (op == "sub")
            dRes = dVal1 - dVal2;
        else if (op == "mul")
            dRes = dVal1 * dVal2;
        else if (op == "div") {
            if (dVal2 == 0) {
                throw MyException("Divide by zero");
            }
            dRes = dVal1 / dVal2;
        } else if (op == "mod")
            throw MyException("Float Modulo");
        else {
            return "0";
        }
        res << std::fixed << dRes;
        tmp = res.str();
        while (tmp.back() == '0')
            tmp.resize(tmp.length() - 1);
    }
    return tmp;
}

int sIntCmp(std::string const &a, std::string const &b) {
    std::istringstream val1(a);
    std::istringstream val2(b);
    int64_t iVal1, iVal2;

    val1 >> iVal1;
    val2 >> iVal2;
    if (iVal1 > iVal2) {
        return 1;
    } else if (iVal1 < iVal2) {
        return -1;
    }
    return 0;
}

int sFloatCmp(std::string const &a, std::string const &b) {
    std::istringstream val1(a);
    std::istringstream val2(b);
    double dVal1, dVal2;

    val1 >> dVal1;
    val2 >> dVal2;
    if (dVal1 > dVal2) {
        return 1;
    } else if (dVal1 < dVal2) {
        return -1;
    }
    return 0;
}