#pragma once

#include "base_exception.h"

#include <cstdio>

BaseException::BaseException(const char *info, const std::source_location &loc) noexcept
{
    snprintf(message, EXCEPTION_MESSAGE_SIZE, "File: %s (%d:%d) `%s`: %s\n", loc.file_name(), loc.line(),
             loc.column(), loc.function_name(), info);
}

const char *BaseException::what() const noexcept { return message; }
