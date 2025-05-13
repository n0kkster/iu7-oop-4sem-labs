#include "SceneException.h"

SceneException::SceneException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

SceneIdOutOfRangeException::SceneIdOutOfRangeException(const char *info,
                                                       const std::source_location &loc) noexcept :
    SceneException(info, loc) { };
