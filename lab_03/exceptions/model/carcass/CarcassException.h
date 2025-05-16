#pragma once

#include "../ModelException.h"

class CarcassException : public ModelException
{
public:
    CarcassException(const char *info,
                     const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidVerticesCountException : public CarcassException
{
public:
    CarcassInvalidVerticesCountException(
        const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidVertexException : public CarcassException
{
public:
    CarcassInvalidVertexException(const char *info,
                                  const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidStructureException : public CarcassException
{
public:
    CarcassInvalidStructureException(
        const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidEdgeException : public CarcassException
{
public:
    CarcassInvalidEdgeException(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidRepresentation : public CarcassException
{
public:
    CarcassInvalidRepresentation(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

class CarcassInvalidFileFormat : public CarcassException
{
public:
    CarcassInvalidFileFormat(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

