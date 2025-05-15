#include "Vertex.h"

#include "../../../../../matrix/matrix.h"

#include <iostream>
#include <math.h>
#include <ostream>

#pragma region Constructors

Vertex::Vertex(const double x, const double y, const double z) noexcept : m_x(x), m_y(y), m_z(z) { }

#pragma endregion

#pragma region Getters

double Vertex::getX() const noexcept
{
    return m_x;
}

double Vertex::getY() const noexcept
{
    return m_y;
}

double Vertex::getZ() const noexcept
{
    return m_z;
}

double Vertex::getW() const noexcept
{
    return m_w;
}

#pragma endregion

#pragma region Setters

void Vertex::setX(const double x) noexcept
{
    m_x = x;
}

void Vertex::setY(const double y) noexcept
{
    m_y = y;
}

void Vertex::setZ(const double z) noexcept
{
    m_z = z;
}

void Vertex::setW(const double w) noexcept
{
    m_w = w;
}

#pragma endregion

double Vertex::calcDistance(const Vertex &other) const noexcept
{
    return std::sqrt(std::pow(other.m_x - m_x, 2) + std::pow(other.m_y - m_y, 2)
                     + std::pow(other.m_z - m_z, 2));
}

void Vertex::transform(const Matrix<double> &matrix)
{
    Matrix<double> curr = { { m_x }, { m_y }, { m_z }, { 1 } };

    Matrix<double> new_pos = matrix * curr;

    m_x = new_pos[0][0];
    m_y = new_pos[1][0];
    m_z = new_pos[2][0];
    m_w = new_pos[3][0];
}

#pragma region Operators

bool Vertex::operator==(const Vertex &other) const noexcept
{
    const double eps = 1e-9;
    return (std::abs(m_x - other.m_x) <= eps) && (std::abs(m_y - other.m_y) <= eps)
        && (std::abs(m_z - other.m_z) <= eps);
}

bool Vertex::equal(const Vertex &other) const noexcept
{
    return *this == other;
}

bool Vertex::operator!=(const Vertex &other) const noexcept
{
    return !(*this == other);
}

bool Vertex::notEqual(const Vertex &other) const noexcept
{
    return *this != other;
}

Vertex &Vertex::add(const Vertex &other) noexcept
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;

    return *this;
}

Vertex &Vertex::operator+=(const Vertex &other) noexcept
{
    add(other);
    return *this;
}

Vertex Vertex::make_sum(const Vertex &other) const
{
    Vertex res(*this);
    res += other;
    return res;
}

Vertex Vertex::operator+(const Vertex &other) const
{
    return make_sum(other);
}

Vertex &Vertex::subtract(const Vertex &other) noexcept
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;

    return *this;
}

Vertex &Vertex::operator-=(const Vertex &other) noexcept
{
    subtract(other);
    return *this;
}

Vertex Vertex::make_diff(const Vertex &other) const
{
    Vertex res(*this);
    res -= other;
    return res;
}

Vertex Vertex::operator-(const Vertex &other) const
{
    return make_diff(other);
}

#pragma endregion

std::ostream &operator<<(std::ostream &os, const Vertex &vertex)
{
    os << "(" << vertex.getX() << ", " << vertex.getY() << ", " << vertex.getZ() << ")";
    return os;
}
