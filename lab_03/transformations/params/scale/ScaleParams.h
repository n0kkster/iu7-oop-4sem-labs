#pragma once

#include "../../../component/primitive/visible/model/carcass/vertex/vertex.h"

class ScaleParams
{
private:
    double m_kx, m_ky, m_kz;

public:
    ScaleParams() noexcept = default;
    ScaleParams(double kx, double ky, double kz) noexcept;
    ScaleParams(const Vertex &vertex) noexcept;

    double getKx() const noexcept;
    double getKy() const noexcept;
    double getKz() const noexcept;
};