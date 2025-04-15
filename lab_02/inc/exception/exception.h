#pragma once

#include "base_exception.h"
#include <source_location>

class IteratorException : BaseException
{
public:
    IteratorException(const char *info, const std::source_location &loc = std::source_location::current());

    const char *what() const noexcept override;
};

class SetException : BaseException
{
public:
    SetException(const char *info, const std::source_location &loc = std::source_location::current());

    const char *what() const noexcept override;
};

class MemoryException : BaseException
{
public:
    MemoryException(const char *info, const std::source_location &loc = std::source_location::current());

    const char *what() const noexcept override;
};

#include "exception.hpp"
