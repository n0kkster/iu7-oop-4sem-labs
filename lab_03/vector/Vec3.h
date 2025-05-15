#pragma once

#include "../component/primitive/visible/model/vertex/Vertex.h"
#include "../concepts/concepts.h"

#include <iostream>

template <ConvertibleToDouble T>
class Vec3
{
private:
    T m_x, m_y, m_z;

public:
    Vec3();
    Vec3(T x, T y, T z);
    Vec3(const Vertex &v);
    explicit Vec3(T val);

    ~Vec3() = default;

    T getX() const noexcept;

    T getY() const noexcept;

    T getZ() const noexcept;

    void setX(const T &x) noexcept;

    void setY(const T &y) noexcept;

    void setZ(const T &z) noexcept;

    Vec3 operator+(const Vec3 &other) const noexcept;
    Vec3 operator-(const Vec3 &other) const noexcept;
    Vec3 operator*(const T &scalar) const noexcept;
    Vec3 operator/(const T &scalar) const;
    Vec3 operator*(const Vec3 &other) const noexcept;

    T dot(const Vec3 &other) const noexcept;
    Vec3 cross(const Vec3 &other) const noexcept;
    T length() const noexcept;
    Vec3 normalized() const;

    bool operator==(const Vec3 &other) const;
    bool operator!=(const Vec3 &other) const;

    static Vec3 zero();
    static Vec3 one();
    static Vec3 up();
    static Vec3 right();
    static Vec3 forward();
};

template <ConvertibleToDouble T>
Vec3<T> operator*(T scalar, const Vec3<T> &vec);

#include "Vec3.hpp"
