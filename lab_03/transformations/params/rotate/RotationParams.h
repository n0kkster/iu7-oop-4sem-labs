#pragma once

#include "../../../component/primitive/visible/model/vertex/Vertex.h"

class RotationParams
{
private:
    double m_angX, m_angY, m_angZ;

public:
    RotationParams() noexcept = default;
    RotationParams(double angX, double angY, double angZ) noexcept;
    RotationParams(const Vertex &vertex) noexcept;

    double getAngleX() const noexcept;
    double getAngleY() const noexcept;
    double getAngleZ() const noexcept;
};