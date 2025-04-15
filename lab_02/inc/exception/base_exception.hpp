#pragma once

#include "base_exception.h"

#include <sstream>

BaseException::BaseException(const std::string &info, const std::source_location &loc)
{
    std::stringstream ss;
    ss  << "File: "
        << loc.file_name() << '('
        << loc.line() << ':'
        << loc.column() << ") `"
        << loc.function_name() << "`: "
        << info << '\n';
    message = ss.str();
}

const char *BaseException::what() const noexcept
{
    return message.c_str();
}

