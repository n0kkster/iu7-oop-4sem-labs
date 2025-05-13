#pragma once

#include "../BaseException.h"

class BaseManagerException : public BaseException
{
public:
    BaseManagerException(const char *info,
                   const std::source_location &loc = std::source_location::current()) noexcept;
};