#pragma once

#include "../BaseException.h"

class ModelException : public BaseException
{
public:
    ModelException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidVerticesCountException : public ModelException
{
public:
    ModelInvalidVerticesCountException(
        const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidVertexException : public ModelException
{
public:
    ModelInvalidVertexException(const char *info,
                                  const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidStructureException : public ModelException
{
public:
    ModelInvalidStructureException(
        const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidEdgeException : public ModelException
{
public:
    ModelInvalidEdgeException(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidRepresentation : public ModelException
{
public:
    ModelInvalidRepresentation(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

class ModelInvalidFileFormat : public ModelException
{
public:
    ModelInvalidFileFormat(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

