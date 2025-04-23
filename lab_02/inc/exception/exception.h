#pragma once

#include "base_exception.h"
#include <source_location>

class IteratorException : public BaseException
{
public:
    IteratorException(const char *info,
                      const std::source_location &loc = std::source_location::current()) noexcept;
};

class SetException : public BaseException
{
public:
    SetException(const char *info,
                 const std::source_location &loc = std::source_location::current()) noexcept;
};

class MemoryException : public SetException
{
public:
    MemoryException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

#include "exception.hpp"
