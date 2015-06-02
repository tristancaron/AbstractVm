#ifndef INT32_HPP
# define INT32_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "FactoryOperand.hpp"

class Int32 : public IOperand {
public:
    Int32(std::string const &value);
    Int32(Int32 const &src);

    Int32 &operator=(Int32 const &src);
    virtual int getPrecision(void) const;
    virtual eOperandType getType(void) const;

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;
    virtual std::string const &toString(void) const;
    virtual ~Int32(void);

private:
    std::string  _sValue;
    eOperandType _type;
    FactoryOperand _factoryOperand;
};
#endif