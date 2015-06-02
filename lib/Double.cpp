#include "Double.hpp"

#include "boost/lexical_cast.hpp"

#include "Utils.hpp"

Double::Double(std::string const &value) : _sValue(value),
                                         _type(DOUBLE) {
    try {
        boost::lexical_cast<double>(value);
    } catch (...) {
        if (sFloatCmp(value, "1") == 1)
            throw std::out_of_range("Overflow");
        if (sFloatCmp(value, "-1") == -1)
            throw std::out_of_range("Underflow");
    }
}

int Double::getPrecision(void) const {
    return _type;
}

eOperandType Double::getType(void) const {
    return (_type);
}

IOperand const* Double::operator%(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue, rhs.toString(), type, "mod"));
}

IOperand const* Double::operator*(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue, rhs.toString(), type, "mul"));
}

IOperand const* Double::operator+(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue, rhs.toString(), type, "add"));
}

IOperand const* Double::operator-(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue, rhs.toString(), type, "sub"));
}

IOperand const* Double::operator/(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue, rhs.toString(), type, "div"));
}

std::string const& Double::toString(void) const {
    return _sValue;
}

Double::~Double(void) {
}

Double::Double(Double const &src) {
    *this = src;
}

Double& Double::operator=(Double const &src) {
    if (this != &src) {
        _sValue = src.toString();
        _type = src.getType();
    }
    return *this;
}