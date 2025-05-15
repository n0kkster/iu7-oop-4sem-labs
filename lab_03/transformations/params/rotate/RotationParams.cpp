#include "RotationParams.h"

RotationParams::RotationParams(double angX, double angY, double angZ, double cx, double cy,
                               double cz) noexcept :
    m_angX(angX), m_angY(angY), m_angZ(angZ), m_cx(cx), m_cy(cy), m_cz(cz)
{ }

double RotationParams::getAngleX() const noexcept
{
    return m_angX;
}

double RotationParams::getAngleY() const noexcept
{
    return m_angY;
}

double RotationParams::getAngleZ() const noexcept
{
    return m_angZ;
}

double RotationParams::getCenterX() const noexcept
{
    return m_cx;
}

double RotationParams::getCenterY() const noexcept
{
    return m_cy;
}

double RotationParams::getCenterZ() const noexcept
{
    return m_cz;
}

