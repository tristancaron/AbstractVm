#include "MyException.hpp"

MyException::MyException(std::string msg) : _msg(msg) {
}

MyException::MyException(const char *msg) : _msg(msg) {
}

MyException::~MyException(void) {
}

const char* MyException::what(void) const throw() {
    return _msg.c_str();
}