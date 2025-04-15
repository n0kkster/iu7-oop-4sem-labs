#pragma once

#include "base_exception.h"
#include <source_location>

class IteratorException : BaseException
{
public:
    IteratorException(const char *info, const std::source_location &loc = std::source_location::current());
};

class SetException : BaseException
{
public:
    SetException(const char *info, const std::source_location &loc = std::source_location::current());
};

class MemoryException : BaseException
{
public:
    MemoryException(const char *info, const std::source_location &loc = std::source_location::current());
};

#include "exception.hpp"
