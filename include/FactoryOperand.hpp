#ifndef FACTORY_OPERAND_HPP
# define FACTORY_OPERAND_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"

class FactoryOperand {
public:
    FactoryOperand(void);
    ~FactoryOperand(void);

    IOperand const *createOperand(eOperandType type, std::string const &value) const;
    IOperand const *createInt8(std::string const &value) const;
    IOperand const *createInt16(std::string const &value) const;
    IOperand const *createInt32(std::string const &value) const;
    IOperand const *createFloat(std::string const &value) const;
    IOperand const *createDouble(std::string const &value) const;
};

#endif