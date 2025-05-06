#pragma once

#include "../../../../matrix/matrix.h"
#include "../../../../transformations/actions/TransformAction.h"
#include "../InvisibleObject.h"

#include <memory>

class BaseCamera : public InvisibleObject
{
public:
    BaseCamera();
    virtual ~BaseCamera() = default;

    virtual const Matrix<double> &getOrientation() const noexcept = 0;
    virtual void setOrientation(const Matrix<double> &orientation) = 0;
    virtual void setViewpoint(const Vertex &viewpoint) noexcept = 0;
    virtual void transform(const std::shared_ptr<const TransformAction> action) = 0;
};
