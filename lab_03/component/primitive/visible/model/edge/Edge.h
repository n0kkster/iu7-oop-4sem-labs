#pragma once

#include <cstddef>

class Edge
{
private:
    size_t m_start, m_end;

public:
#pragma region Constructor
    Edge() = default;
    Edge(size_t start, size_t end);

    Edge(const Edge &) = default;
    Edge(Edge &&) = default;
#pragma endregion

#pragma region Assignment
    Edge &operator=(const Edge &) = default;
    Edge &operator=(Edge &&) = default;
#pragma endregion

    size_t getStart() const;
    size_t getEnd() const;

    void setStart(size_t start);
    void setEnd(size_t end);
};
