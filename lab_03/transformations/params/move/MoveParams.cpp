#include "MoveParams.h"

MoveParams::MoveParams(double dx, double dy, double dz) noexcept : m_dx(dx), m_dy(dy), m_dz(dz) { }

MoveParams::MoveParams(const Vertex &vertex) noexcept :
    m_dx(vertex.getX()), m_dy(vertex.getY()), m_dz(vertex.getZ())
{ }

double MoveParams::getOffsetX() const noexcept { return m_dx; }

double MoveParams::getOffsetY() const noexcept { return m_dy; }

double MoveParams::getOffsetZ() const noexcept { return m_dz; }
