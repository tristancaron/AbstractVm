#include "Int32.hpp"

#include "boost/lexical_cast.hpp"

#include "Utils.hpp"

Int32::Int32(std::string const &value) : _sValue(value),
                                         _type(INT32) {
    try {
        boost::lexical_cast<int32_t>(value);
    } catch (...) {
        if (sIntCmp(value, "1") == 1)
            throw std::out_of_range("Overflow");
        if (sIntCmp(value, "-1") == -1)
            throw std::out_of_range("Underflow");
    }
}

int Int32::getPrecision(void) const {
    return _type;
}

eOperandType Int32::getType(void) const {
    return (_type);
}

IOperand const* Int32::operator%(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mod"));
}

IOperand const* Int32::operator*(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "mul"));
}

IOperand const* Int32::operator+(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "add"));
}

IOperand const* Int32::operator-(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "sub"));
}

IOperand const* Int32::operator/(IOperand const &rhs) const {
    eOperandType type = (getPrecision() >= rhs.getPrecision()) ?
            getType() : rhs.getType();
    return _factoryOperand.createOperand(type, calculated(_sValue,
            rhs.toString(), type, "div"));
}

std::string const& Int32::toString(void) const {
    return _sValue;
}

Int32::~Int32(void) {
}

Int32::Int32(Int32 const &src) {
    *this = src;
}

Int32& Int32::operator=(Int32 const &src) {
    if (this != &src) {
        _sValue = src.toString();
        _type = src.getType();
    }
    return *this;
}