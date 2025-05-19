#pragma once

#include "../BaseCamera.h"
#include "../../../../../vector/Vec3.h"

class DefaultCamera final : public BaseCamera
{
private:
    Vertex m_viewpoint;

    Vec3<double> m_up;
    Vec3<double> m_right;
    Vec3<double> m_forward;

    double m_fov;
    double m_near;
    double m_far;

public:
    DefaultCamera();
    DefaultCamera(const Vertex &viewpoint);

    virtual ~DefaultCamera() override = default;

    const Matrix<double> getLookMatrix() const noexcept override;
    const Matrix<double> getProjectionMatrix(double aspectRatio) const override;

    void transform(const std::shared_ptr<const TransformAction> action) override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    Vertex getCenter() const noexcept override;
};
