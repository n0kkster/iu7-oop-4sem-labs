#pragma once

#include "base_exception.h"
#include <source_location>

class IteratorException : public BaseException
{
public:
    IteratorException(const char *info, const std::source_location &loc = std::source_location::current());
};

class SetException : public BaseException
{
public:
    SetException(const char *info, const std::source_location &loc = std::source_location::current());
};

class MemoryException : public BaseException
{
public:
    MemoryException(const char *info, const std::source_location &loc = std::source_location::current());
};

class OutOfRangeException : public BaseException
{
public:
    OutOfRangeException(const char *info, const std::source_location &loc = std::source_location::current());
};

#include "exception.hpp"
