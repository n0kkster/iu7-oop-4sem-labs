#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <string>
#include <source_location>

class BaseException : public std::exception
{
protected:
    std::string message;

public:
    BaseException(const std::string &info, const std::source_location &loc = std::source_location::current());
    virtual const char *what() const noexcept override;
};

#include "base_exception.hpp"

#endif /* BASE_EXCEPTION_H */
