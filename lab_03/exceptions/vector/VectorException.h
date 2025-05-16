#pragma once

#include "../BaseException.h"

class VectorException : public BaseException
{
public:
    VectorException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

class VectorDivisionByZeroException : public VectorException
{
public:
    VectorDivisionByZeroException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};
