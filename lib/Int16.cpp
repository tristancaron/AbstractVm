#include "Int16.hpp"

#include "boost/lexical_cast.hpp"

#include "Utils.hpp"

Int16::Int16(std::string const &value) : _sValue(value),
                _type(INT16) {
    try {
        boost::lexical_cast<int16_t>(value);
    } catch (...) {
        if (sIntCmp(value, "1") == 1)
            throw std::out_of_range("Overflow");
        if (sIntCmp(value, "-1") == -1)
            throw std::out_of_range("Underflow");
    }
}

int Int16::getPrecision(void) const {
    return _type;
}

eOperandType Int16::getType(void) const {
    return (_type);
}

IOperand const* Int16::operator%(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mod"));
}

IOperand const* Int16::operator*(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mul"));
}

IOperand const* Int16::operator+(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "add"));
}

IOperand const* Int16::operator-(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "sub"));
}

IOperand const* Int16::operator/(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "div"));
}

std::string const& Int16::toString(void) const {
    return _sValue;
}

Int16::~Int16(void) {
}

Int16::Int16(Int16 const &src) {
    *this = src;
}

Int16& Int16::operator=(Int16 const &src) {
    if (this != &src) {
        _sValue = src.toString();
        _type = src.getType();
    }
    return *this;
}