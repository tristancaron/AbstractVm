#ifndef DOUBLE_HPP
# define DOUBLE_HPP

# include <iostream>

# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "FactoryOperand.hpp"

class Double : public IOperand {
public:
    Double(std::string const &value);
    Double(Double const &src);

    Double &operator=(Double const &src);

    virtual int getPrecision(void) const;
    virtual eOperandType getType(void) const;

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;
    virtual std::string const &toString(void) const;
    virtual ~Double(void);

private:
    std::string _sValue;
    eOperandType _type;
    FactoryOperand _factoryOperand;
};

#endif