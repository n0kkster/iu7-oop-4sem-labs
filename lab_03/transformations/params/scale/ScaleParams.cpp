#include "ScaleParams.h"

ScaleParams::ScaleParams(double kx, double ky, double kz) noexcept : m_kx(kx), m_ky(ky), m_kz(kz) { }

ScaleParams::ScaleParams(const Vertex &vertex) noexcept :
    m_kx(vertex.getX()), m_ky(vertex.getY()), m_kz(vertex.getZ())
{ }

double ScaleParams::getKx() const noexcept { return m_kx; }

double ScaleParams::getKy() const noexcept { return m_ky; }

double ScaleParams::getKz() const noexcept { return m_kz; }
