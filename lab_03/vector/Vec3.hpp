#pragma once

#include "Vec3.h"

#include <cmath>
#include <stdexcept>

template <ConvertibleToDouble T>
Vec3<T>::Vec3() : m_x(0), m_y(0), m_z(0)
{ }

template <ConvertibleToDouble T>
Vec3<T>::Vec3(T x, T y, T z) : m_x(x), m_y(y), m_z(z)
{ }

template <ConvertibleToDouble T>
Vec3<T>::Vec3(T val) : m_x(val), m_y(val), m_z(val)
{ }

template <ConvertibleToDouble T>
Vec3<T>::Vec3(const Vertex &v) : m_x(v.getX()), m_y(v.getY()), m_z(v.getZ())
{ }

template <ConvertibleToDouble T>
T Vec3<T>::getX() const noexcept
{
    return m_x;
}

template <ConvertibleToDouble T>
T Vec3<T>::getY() const noexcept
{
    return m_y;
}

template <ConvertibleToDouble T>
T Vec3<T>::getZ() const noexcept
{
    return m_z;
}

template <ConvertibleToDouble T>
void Vec3<T>::setX(const T &x) noexcept
{
    m_x = x;
}

template <ConvertibleToDouble T>
void Vec3<T>::setY(const T &y) noexcept
{
    m_y = y;
}

template <ConvertibleToDouble T>
void Vec3<T>::setZ(const T &z) noexcept
{
    m_z = z;
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::operator+(const Vec3 &other) const noexcept
{
    return Vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::operator-(const Vec3 &other) const noexcept
{
    return Vec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::operator*(const T &scalar) const noexcept
{
    return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::operator/(const T &scalar) const
{
    if (scalar == 0)
        throw std::runtime_error("Division by zero");
    return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::operator*(const Vec3 &other) const noexcept
{
    return Vec3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
}

template <ConvertibleToDouble T>
T Vec3<T>::dot(const Vec3 &other) const noexcept
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::cross(const Vec3 &other) const noexcept
{
    return Vec3(m_y * other.m_z - m_z * other.m_y, m_z * other.m_x - m_x * other.m_z,
                m_x * other.m_y - m_y * other.m_x);
}

template <ConvertibleToDouble T>
T Vec3<T>::length() const noexcept
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::normalized() const
{
    T len = length();
    if (len == 0)
        return *this;
    return *this / len;
}

template <ConvertibleToDouble T>
bool Vec3<T>::operator==(const Vec3 &other) const
{
    return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

template <ConvertibleToDouble T>
bool Vec3<T>::operator!=(const Vec3 &other) const
{
    return !(*this == other);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::zero()
{
    return Vec3(0, 0, 0);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::one()
{
    return Vec3(1, 1, 1);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::up()
{
    return Vec3(0, 1, 0);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::right()
{
    return Vec3(1, 0, 0);
}

template <ConvertibleToDouble T>
Vec3<T> Vec3<T>::forward()
{
    return Vec3(0, 0, -1);
}

template <ConvertibleToDouble T>
Vec3<T> operator*(T scalar, const Vec3<T> &vec)
{
    return vec * scalar;
}

template <ConvertibleToDouble T>
std::ostream &operator<<(std::ostream &os, const Vec3<T> &vec)
{
    os << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
    return os;
}
