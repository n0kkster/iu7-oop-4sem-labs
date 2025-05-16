#include "VectorException.h"

VectorException::VectorException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

VectorDivisionByZeroException::VectorDivisionByZeroException(const char *info, const std::source_location &loc) noexcept :
    VectorException(info, loc) { };