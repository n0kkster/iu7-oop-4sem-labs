#include "CompositeException.h"

CompositeException::CompositeException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

CompositeOutOfRangeException::CompositeOutOfRangeException(const char *info,
                                                           const std::source_location &loc) noexcept :
    CompositeException(info, loc) { };
