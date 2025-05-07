#include "ModelException.h"

ModelException::ModelException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };