#pragma once

#include <cstdio>
#include "base_exception.h"

BaseException::BaseException(const char *info, const std::source_location &loc)
{
    snprintf(message, EXCEPTION_MESSAGE_SIZE, "File: %s (%d:%d) `%s`: %s\n", loc.file_name(), loc.line(),
             loc.column(), loc.function_name(), info);
}

const char *BaseException::what() const noexcept { return message; }
