#pragma once

#include <cstddef>

enum DirectorIds : size_t
{
    CarcassDirectorId = 0,
    CameraDirectorId,
    CompositeDirectorId
};

enum ReaderIds : size_t
{
    CarcassTxtReaderId = 0,
    CarcassObjReaderId,
    CarcassCsvReaderId,
    CameraTxtReaderId,
    CameraObjReaderId,
    CompositeTxtReaderId,
    CompositeObjReaderId
};