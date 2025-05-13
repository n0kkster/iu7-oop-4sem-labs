#include "CameraManagerException.h"

CameraManagerException::CameraManagerException(const char *info, const std::source_location &loc) noexcept :
    BaseManagerException(info, loc) { };

CameraManagerInvalidIdException::CameraManagerInvalidIdException(const char *info, const std::source_location &loc) noexcept :
    CameraManagerException(info, loc) { };