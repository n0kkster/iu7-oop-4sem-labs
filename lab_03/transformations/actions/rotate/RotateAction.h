#pragma once

#include "../../params/rotate/RotationParams.h"
#include "../TransformAction.h"

class RotateAction : public TransformAction
{
private:
    Matrix<double> createRotationX(const double angle);
    Matrix<double> createRotationY(const double angle);
    Matrix<double> createRotationZ(const double angle);

public:
    RotateAction() = default;
    virtual ~RotateAction() override = default;

    RotateAction(const RotationParams &params);

    bool isMoveAction() const noexcept override;
};
