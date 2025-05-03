#pragma once

class Vertex
{
private:
    double m_x, m_y, m_z;

public:
#pragma region Constructors
    Vertex() = default;
    Vertex(const double x, const double y, const double z);
#pragma endregion

#pragma region Destructor
    ~Vertex() = default;
#pragma endregion

#pragma region Getters
    double getX() const;
    double getY() const;
    double getZ() const;
#pragma endregion

#pragma region Setters
    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);
#pragma endregion

    double calcDistance(const Vertex &other) const noexcept;
    void transform(const auto &matrix) noexcept;

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
