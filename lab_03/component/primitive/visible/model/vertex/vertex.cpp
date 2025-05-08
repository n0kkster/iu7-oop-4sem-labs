#include "vertex.h"

#include <math.h>

#pragma region Constructors

Vertex::Vertex(const double x, const double y, const double z) noexcept : m_x(x), m_y(y), m_z(z) { }

#pragma endregion

#pragma region Getters

double Vertex::getX() const noexcept
{
    return this->m_x;
}

double Vertex::getY() const noexcept
{
    return this->m_y;
}

double Vertex::getZ() const noexcept
{
    return this->m_z;
}

#pragma endregion

#pragma region Setters

void Vertex::setX(const double x) noexcept
{
    this->m_x = x;
}

void Vertex::setY(const double y) noexcept
{
    this->m_y = y;
}

void Vertex::setZ(const double z) noexcept
{
    this->m_z = z;
}

#pragma endregion

double Vertex::calcDistance(const Vertex &other) const noexcept
{
    return std::sqrt(std::pow(other.m_x - this->m_x, 2) + std::pow(other.m_y - this->m_y, 2)
                     + std::pow(other.m_z - this->m_z, 2));
}

void Vertex::transform(const Matrix<double> &matrix)
{
    Matrix<double> curr = {
        { this->m_x, this->m_y, this->m_z, 1 }
    };
    Matrix<double> new_pos = curr * matrix;

    this->m_x = new_pos[0][0];
    this->m_y = new_pos[0][1];
    this->m_z = new_pos[0][2];
}

#pragma region Operators

bool Vertex::operator==(const Vertex &other) const noexcept
{
    const double eps = 1e-9;
    return (std::abs(this->m_x - other.m_x) <= eps) && (std::abs(this->m_y - other.m_y) <= eps) && (std::abs(this->m_z - other.m_z) <= eps);
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
    this->m_x += other.m_x;
    this->m_y += other.m_y;
    this->m_z += other.m_z;

    return *this;
}

Vertex &Vertex::operator+=(const Vertex &other) noexcept
{
    this->add(other);
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
    return this->make_sum(other);
}

Vertex &Vertex::subtract(const Vertex &other) noexcept
{
    this->m_x -= other.m_x;
    this->m_y -= other.m_y;
    this->m_z -= other.m_z;

    return *this;
}

Vertex &Vertex::operator-=(const Vertex &other) noexcept
{
    this->subtract(other);
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
    return this->make_diff(other);
}

#pragma endregion
