#include "Int8.hpp"

#include "boost/numeric/conversion/cast.hpp"
#include "boost/lexical_cast.hpp"

#include "Utils.hpp"

Int8::Int8(std::string const &value) : _sValue(value), _type(INT8) {
    try {
        boost::numeric_cast<int8_t>(boost::lexical_cast<int>(value));
    } catch (...) {
        if (sIntCmp(value, "1") == 1)
            throw std::out_of_range("Overflow");
        if (sIntCmp(value, "-1") == -1)
            throw std::out_of_range("Underflow");
    }
}

int Int8::getPrecision(void) const {
    return _type;
}

eOperandType Int8::getType(void) const {
    return (_type);
}

IOperand const* Int8::operator%(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mod"));
}

IOperand const* Int8::operator*(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mul"));
}

IOperand const* Int8::operator+(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "add"));
}

IOperand const* Int8::operator-(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "sub"));
}

IOperand const* Int8::operator/(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "div"));
}

std::string const& Int8::toString(void) const {
    return _sValue;
}

Int8::~Int8(void) {
}

Int8::Int8(Int8 const &src) {
    *this = src;
}

Int8& Int8::operator=(Int8 const &src) {
    if (this != &src) {
        _sValue = src.toString();
        _type = src.getType();
    }
    return *this;
}