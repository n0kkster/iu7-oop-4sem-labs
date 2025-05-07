#include "CarcassException.h"

CarcassException::CarcassException(const char *info, const std::source_location &loc) noexcept :
    ModelException(info, loc) { };

CarcassInvalidVerticesCountException::CarcassInvalidVerticesCountException(
    const char *info, const std::source_location &loc) noexcept : CarcassException(info, loc) { };

CarcassInvalidVertexException::CarcassInvalidVertexException(const char *info,
                                                             const std::source_location &loc) noexcept :
    CarcassException(info, loc) { };

CarcassInvalidStructureException::CarcassInvalidStructureException(const char *info,
                                                                   const std::source_location &loc) noexcept :
    CarcassException(info, loc) { };

CarcassInvalidEdgeException::CarcassInvalidEdgeException(const char *info,
                                                         const std::source_location &loc) noexcept :
    CarcassException(info, loc) { };
