#include "Float.hpp"

#include "boost/lexical_cast.hpp"

#include "Utils.hpp"

Float::Float(std::string const &value) : _sValue(value),
                                           _type(FLOAT) {
    try {
        boost::lexical_cast<float>(value);
    } catch (...) {
        if (sFloatCmp(value, "1") == 1)
            throw std::out_of_range("Overflow");
        if (sFloatCmp(value, "-1") == -1)
            throw std::out_of_range("Underflow");
    }
}

int Float::getPrecision(void) const {
    return _type;
}

eOperandType Float::getType(void) const {
    return (_type);
}

IOperand const* Float::operator%(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mod"));
}

IOperand const* Float::operator*(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mul"));
}

IOperand const* Float::operator+(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "add"));
}

IOperand const* Float::operator-(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "sub"));
}

IOperand const* Float::operator/(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "div"));
}

std::string const& Float::toString(void) const {
    return _sValue;
}

Float::~Float(void) {
}

Float::Float(Float const &src) {
    *this = src;
}

Float& Float::operator=(Float const &src) {
    if (this != &src) {
        _sValue = src.toString();
        _type = src.getType();
    }
    return *this;
}