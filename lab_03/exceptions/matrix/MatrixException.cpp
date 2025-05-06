#include "MatrixException.h"

MatrixException::MatrixException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

MatrixMemoryException::MatrixMemoryException(const char *info, const std::source_location &loc) noexcept :
    MatrixException(info, loc) { };

InvalidInitListSizeException::InvalidInitListSizeException(const char *info,
                                                           const std::source_location &loc) noexcept :
    MatrixException(info, loc) { };

IncompatibleDimensionsException::IncompatibleDimensionsException(const char *info,
                                                                 const std::source_location &loc) noexcept :
    MatrixException(info, loc) { };

MatrixOutOfRangeException::MatrixOutOfRangeException(const char *info,
                                                     const std::source_location &loc) noexcept :
    MatrixException(info, loc) { };
