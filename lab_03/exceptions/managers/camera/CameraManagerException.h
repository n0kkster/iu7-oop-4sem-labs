#pragma once

#include "../BaseManagerException.h"

class CameraManagerException : public BaseManagerException
{
public:
    CameraManagerException(const char *info,
                   const std::source_location &loc = std::source_location::current()) noexcept;
};

class CameraManagerInvalidIdException : public CameraManagerException
{
public:
    CameraManagerInvalidIdException(const char *info,
                   const std::source_location &loc = std::source_location::current()) noexcept;
};