#include "FactoryOperand.hpp"

# include "Int8.hpp"
# include "Int16.hpp"
# include "Int32.hpp"
# include "Double.hpp"
# include "Float.hpp"

FactoryOperand::FactoryOperand(void) {
}

FactoryOperand::~FactoryOperand(void) {
}

IOperand const* FactoryOperand::createOperand(eOperandType type, std::string
const &value) const {
    switch (type) {
        case INT8:
            return createInt8(value);
        case INT16:
            return createInt16(value);
        case INT32:
            return createInt32(value);
        case FLOAT:
            return createFloat(value);
        case DOUBLE:
            return createDouble(value);
        default:
            return nullptr;
    }
}

IOperand const* FactoryOperand::createInt8(std::string const &value) const {
    return new Int8(value);
}

IOperand const* FactoryOperand::createInt16(std::string const &value) const {
    return new Int16(value);
}

IOperand const* FactoryOperand::createInt32(std::string const &value) const {
    return new Int32(value);
}

IOperand const* FactoryOperand::createFloat(std::string const &value) const {
    return new Float(value);
}

IOperand const* FactoryOperand::createDouble(std::string const &value) const {
    return new Double(value);
}