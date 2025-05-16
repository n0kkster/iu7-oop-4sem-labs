#include "CameraException.h"

CameraException::CameraException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

UnknownCameraException::UnknownCameraException(const char *info, const std::source_location &loc) noexcept :
    CameraException(info, loc) { };
