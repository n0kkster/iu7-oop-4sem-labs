#include "ScaleParams.h"

ScaleParams::ScaleParams(double kx, double ky, double kz, double cx, double cy, double cz) noexcept :
    m_kx(kx), m_ky(ky), m_kz(kz), m_cx(cx), m_cy(cy), m_cz(cz)
{ }

double ScaleParams::getKx() const noexcept
{
    return m_kx;
}

double ScaleParams::getKy() const noexcept
{
    return m_ky;
}

double ScaleParams::getKz() const noexcept
{
    return m_kz;
}

double ScaleParams::getCx() const noexcept
{
    return m_cx;
}

double ScaleParams::getCy() const noexcept
{
    return m_cy;
}

double ScaleParams::getCz() const noexcept
{
    return m_cz;
}
