#pragma once

#include "../BaseCamera.h"

class DefaultCamera final : public BaseCamera
{
private:
    Matrix<double> m_orientation;
    Vertex m_viewpoint;

public:
    DefaultCamera();
    DefaultCamera(const Vertex &viewpoint);
    DefaultCamera(const Vertex &viewpoint, const Matrix<double> orientation);

    ~DefaultCamera() override = default;

    const Matrix<double> &getOrientation() const noexcept override;
    void setOrientation(const Matrix<double> &orientation) override;
    void setViewpoint(const Vertex &viewpoint) noexcept override;
    void transform(const std::shared_ptr<const TransformAction> action) override;
    // void accept(/* visitor */);
};
