#ifndef INT8_HPP
# define INT8_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "FactoryOperand.hpp"

class Int8 : public IOperand {
public:
    Int8(std::string const &value);
    Int8(Int8 const &src);

    Int8 &operator=(Int8 const &src);
    virtual int getPrecision(void) const;
    virtual eOperandType getType(void) const;

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;

    virtual std::string const& toString(void) const;
    virtual ~Int8(void);
private:
    std::string       _sValue;
    eOperandType      _type;
    FactoryOperand    _factoryOperand;
};

#endif