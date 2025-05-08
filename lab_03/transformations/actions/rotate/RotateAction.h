#pragma once

#include "../../params/rotate/RotationParams.h"
#include "../TransformAction.h"

class RotateAction : public TransformAction
{
public:
    RotateAction() = default;
    virtual ~RotateAction() override = default;

    RotateAction(const RotationParams &params);
    RotateAction(const Vertex &vertex, const RotationParams &params);

    bool isMoveAction() const noexcept override;
};
