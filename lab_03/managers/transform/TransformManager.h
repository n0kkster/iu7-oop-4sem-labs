#pragma once

#include "../BaseManager.h"
#include "../../transformations/params/move/MoveParams.h"
#include "../../transformations/params/scale/ScaleParams.h"
#include "../../transformations/params/rotate/RotationParams.h"

class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    virtual ~TransformManager() = default;

    void moveObject(size_t id, const MoveParams &params);
    void scaleObject(size_t id, const ScaleParams &params);
    void rotateObject(size_t id, const RotationParams &params);
};