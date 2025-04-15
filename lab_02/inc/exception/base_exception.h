#pragma once

#define EXCEPTION_MESSAGE_SIZE 512

#include <exception>
#include <source_location>

class BaseException : public std::exception
{
protected:
    char message[EXCEPTION_MESSAGE_SIZE];

public:
    BaseException(const char *info, const std::source_location &loc = std::source_location::current());
    virtual const char *what() const noexcept override;
};

#include "base_exception.hpp"
