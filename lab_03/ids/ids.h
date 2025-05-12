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
    CarcassReaderId = 0,
    CameraReaderId,
    CompositeReaderId
};