#pragma once

#include <cstddef>

enum DirectorId : size_t
{
    CarcassDirectorId = 0,
};

enum ReaderId : size_t
{
    CarcassReaderId = 0,
};

enum InternalRepresentationId : size_t
{
    ListInternalReprsentationId = 0,
    MatrixInternalReprsentationId
};

enum CameraId : size_t
{
    DefaultCameraId = 0
};