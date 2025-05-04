#pragma once

#include "../../../../../../matrix/matrix.h"

class Vertex
{
private:
    double m_x, m_y, m_z;

public:
#pragma region Constructors
    Vertex() noexcept = default;
    Vertex(const double x, const double y, const double z) noexcept;

    Vertex(const Vertex &other) = default;
    Vertex(Vertex &&other) = default;
#pragma endregion

#pragma region Destructor
    ~Vertex() = default;
#pragma endregion

#pragma region Assignment
    Vertex &operator=(const Vertex &other) = default;
    Vertex &operator=(Vertex &&other) = default;
#pragma endregion

#pragma region Getters
    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;
#pragma endregion

#pragma region Setters
    void setX(const double x) noexcept;
    void setY(const double y) noexcept;
    void setZ(const double z) noexcept;
#pragma endregion

    double calcDistance(const Vertex &other) const noexcept;
    void transform(const Matrix<double> &matrix);

#pragma region Operators
    bool operator==(const Vertex &other) const noexcept;
    bool equal(const Vertex &other) const noexcept;

    bool operator!=(const Vertex &other) const noexcept;
    bool notEqual(const Vertex &other) const noexcept;

    Vertex &add(const Vertex &other) noexcept;
    Vertex &operator+=(const Vertex &other) noexcept;

    Vertex make_sum(const Vertex &other) const;
    Vertex operator+(const Vertex &other) const;

    Vertex &subtract(const Vertex &other) noexcept;
    Vertex &operator-=(const Vertex &other) noexcept;

    Vertex make_diff(const Vertex &other) const;
    Vertex operator-(const Vertex &other) const;
#pragma endregion
};
