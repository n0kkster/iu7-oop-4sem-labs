#pragma once

#include "../../../component/primitive/visible/model/vertex/vertex.h"

class MoveParams
{
private:
    double m_dx, m_dy, m_dz;

public:
    MoveParams() noexcept = default;
    MoveParams(double dx, double dy, double dz) noexcept;
    MoveParams(const Vertex &vertex) noexcept;

    double getOffsetX() const noexcept;
    double getOffsetY() const noexcept;
    double getOffsetZ() const noexcept;
};