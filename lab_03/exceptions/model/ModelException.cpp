#include "ModelException.h"

ModelException::ModelException(const char *info, const std::source_location &loc) noexcept :
    BaseException(info, loc) { };

ModelInvalidVerticesCountException::ModelInvalidVerticesCountException(
    const char *info, const std::source_location &loc) noexcept : ModelException(info, loc) { };

ModelInvalidVertexException::ModelInvalidVertexException(const char *info,
                                                         const std::source_location &loc) noexcept :
    ModelException(info, loc) { };

ModelInvalidStructureException::ModelInvalidStructureException(const char *info,
                                                               const std::source_location &loc) noexcept :
    ModelException(info, loc) { };

ModelInvalidEdgeException::ModelInvalidEdgeException(const char *info,
                                                     const std::source_location &loc) noexcept :
    ModelException(info, loc) { };

ModelInvalidRepresentation::ModelInvalidRepresentation(const char *info,
                                                       const std::source_location &loc) noexcept :
    ModelException(info, loc) { };

ModelInvalidFileFormat::ModelInvalidFileFormat(const char *info, const std::source_location &loc) noexcept :
    ModelException(info, loc) { };
