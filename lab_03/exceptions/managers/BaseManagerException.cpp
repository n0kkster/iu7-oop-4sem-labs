#include "BaseManagerException.h"

BaseManagerException::BaseManagerException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };