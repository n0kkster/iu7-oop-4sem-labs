#pragma once

#include "../../../transformations/params/move/MoveParams.h"
#include "../TransformVisitor.h"

class MoveVisitor : public TransformVisitor
{
public:
    MoveVisitor() = delete;
    MoveVisitor(const MoveParams &params);

    virtual ~MoveVisitor() override = default;
};
