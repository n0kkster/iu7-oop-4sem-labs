#pragma once

#include "../../../../matrix/matrix.h"
#include "../../../../transformations/actions/TransformAction.h"
#include "../InvisibleObject.h"

#include <memory>

class BaseCamera : public InvisibleObject
{
public:
    BaseCamera() = default;
    virtual ~BaseCamera() override = default;

    virtual const Matrix<double> getLookMatrix() const noexcept = 0;
    virtual const Matrix<double> getProjectionMatrix(double aspectRatio) const = 0;
    virtual void transform(const std::shared_ptr<const TransformAction> action) = 0;
};
