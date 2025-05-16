#pragma once

#include "../BaseException.h"

class CameraException : public BaseException
{
public:
    CameraException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

class UnknownCameraException : public CameraException
{
public:
    UnknownCameraException(const char *info,
                                const std::source_location &loc = std::source_location::current()) noexcept;
};

