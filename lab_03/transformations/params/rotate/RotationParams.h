#pragma once

#include "../../../component/primitive/visible/model/vertex/Vertex.h"

class RotationParams
{
private:
    double m_angX, m_angY, m_angZ;
    double m_cx, m_cy, m_cz;

public:
    RotationParams() noexcept = default;
    RotationParams(double angX, double angY, double angZ, double cx, double cy, double cz) noexcept;

    double getAngleX() const noexcept;
    double getAngleY() const noexcept;
    double getAngleZ() const noexcept;

    double getCenterX() const noexcept;
    double getCenterY() const noexcept;
    double getCenterZ() const noexcept;
};
