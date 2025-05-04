#include "RotationParams.h"

RotationParams::RotationParams(double angX, double angY, double angZ) noexcept :
    m_angX(angX), m_angY(angY), m_angZ(angZ)
{ }

RotationParams::RotationParams(const Vertex &vertex) noexcept :
    m_angX(vertex.getX()), m_angY(vertex.getY()), m_angZ(vertex.getZ())
{ }

double RotationParams::getAngleX() const noexcept { return this->m_angX; }

double RotationParams::getAngleY() const noexcept { return this->m_angY; }

double RotationParams::getAngleZ() const noexcept { return this->m_angZ; }
