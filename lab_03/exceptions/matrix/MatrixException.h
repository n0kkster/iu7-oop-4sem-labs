#pragma once

#include "../BaseException.h"

class MatrixException : public BaseException
{
public:
    MatrixException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

class MatrixMemoryException : public MatrixException
{
public:
    MatrixMemoryException(const char *info,
                          const std::source_location &loc = std::source_location::current()) noexcept;
};

class InvalidInitListSizeException : public MatrixException
{
public:
    InvalidInitListSizeException(const char *info,
                                 const std::source_location &loc = std::source_location::current()) noexcept;
};

class IncompatibleDimensionsException : public MatrixException
{
public:
    IncompatibleDimensionsException(
        const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class MatrixOutOfRangeException : public MatrixException
{
public:
    MatrixOutOfRangeException(const char *info,
                              const std::source_location &loc = std::source_location::current()) noexcept;
};
