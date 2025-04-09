#ifndef BASE_EXCEPTION_HPP
#define BASE_EXCEPTION_HPP

#include "base_exception.h"

#include <sstream>

BaseException::BaseException(const std::string &info, const std::source_location &loc = std::source_location::current())
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

#endif /* BASE_EXCEPTION_H */
