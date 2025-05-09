#pragma once

#include "../../../transformations/params/rotate/RotationParams.h"
#include "../TransformVisitor.h"

class RotateVisitor : public TransformVisitor
{
public:
    RotateVisitor() = delete;
    RotateVisitor(const RotationParams &params);

    virtual ~RotateVisitor() override = default;
};
