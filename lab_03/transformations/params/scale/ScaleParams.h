#pragma once

#include "../../../component/primitive/visible/model/vertex/Vertex.h"

class ScaleParams
{
private:
    double m_kx, m_ky, m_kz;
    double m_cx, m_cy, m_cz;

public:
    ScaleParams() noexcept = default;
    ScaleParams(double kx, double ky, double kz, double cx, double cy, double cz) noexcept;

    double getKx() const noexcept;
    double getKy() const noexcept;
    double getKz() const noexcept;

    double getCx() const noexcept;
    double getCy() const noexcept;
    double getCz() const noexcept;
};