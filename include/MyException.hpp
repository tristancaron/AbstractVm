#ifndef MYEXCEPTION_HPP
# define MYEXCEPTION_HPP

# include <exception>
# include <iostream>

class MyException : public std::exception {
public:
    MyException(const char *msg);
    MyException(std::string msg);
    ~MyException(void);

    virtual const char *what(void) const throw();
private:
    std::string _msg;
};

#endif