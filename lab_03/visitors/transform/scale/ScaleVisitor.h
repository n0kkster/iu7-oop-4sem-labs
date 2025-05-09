#pragma once

#include "../../../transformations/params/scale/ScaleParams.h"
#include "../TransformVisitor.h"

class ScaleVisitor : public TransformVisitor
{
public:
    ScaleVisitor() = delete;
    ScaleVisitor(const ScaleParams &params);

    virtual ~ScaleVisitor() override = default;
};
