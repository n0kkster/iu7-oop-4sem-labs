#pragma once

#include "../BaseException.h"

class CompositeException : public BaseException
{
public:
    CompositeException(const char *info,
                       const std::source_location &loc = std::source_location::current()) noexcept;
};

class CompositeOutOfRangeException : public CompositeException
{
public:
    CompositeOutOfRangeException(const char *info,
                                 const std::source_location &loc = std::source_location::current()) noexcept;
};
