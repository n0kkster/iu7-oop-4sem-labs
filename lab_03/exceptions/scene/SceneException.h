#pragma once

#include "../BaseException.h"

class SceneException : public BaseException
{
public:
    SceneException(const char *info,
                   const std::source_location &loc = std::source_location::current()) noexcept;
};

class SceneIdOutOfRangeException : public SceneException
{
public:
    SceneIdOutOfRangeException(const char *info,
                               const std::source_location &loc = std::source_location::current()) noexcept;
};
