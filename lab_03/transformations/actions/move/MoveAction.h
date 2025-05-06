#pragma once

#include "../../params/move/MoveParams.h"
#include "../TransformAction.h"

class MoveAction : public TransformAction
{
public:
    MoveAction() = default;
    ~MoveAction() override = default;

    MoveAction(const MoveParams &params) noexcept;

    bool isMoveAction() const noexcept override;
};
