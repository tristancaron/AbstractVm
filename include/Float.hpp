#ifndef FLOAT_HPP
# define FLOAT_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "FactoryOperand.hpp"

class Float : public IOperand {
public:
    Float(std::string const &value);
    Float(Float const &src);

    Float &operator=(Float const &src);

    virtual int getPrecision(void) const;
    virtual eOperandType getType(void) const;

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;
    virtual std::string const &toString(void) const;
    virtual ~Float(void);

private:
    std::string  _sValue;
    eOperandType _type;
    FactoryOperand _factoryOperand;
};

#endif