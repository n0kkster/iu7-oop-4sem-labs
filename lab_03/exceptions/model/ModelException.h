#pragma once

#include "../BaseException.h"

class ModelException : public BaseException
{
public:
    ModelException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};
