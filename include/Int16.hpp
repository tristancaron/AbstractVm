#ifndef INT16_HPP
# define INT16_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "FactoryOperand.hpp"

class Int16 : public IOperand {
public:
    Int16(std::string const &value);
    Int16(Int16 const &src);

    Int16 &operator=(Int16 const &src);

    virtual int getPrecision(void) const;
    virtual eOperandType getType(void) const;

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;

    virtual std::string const& toString(void) const;
    virtual ~Int16(void);
private:
    std::string        _sValue;
    eOperandType       _type;
    FactoryOperand     _factoryOperand;
};

#endif