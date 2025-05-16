#pragma once

#include "../../../component/primitive/visible/model/vertex/Vertex.h"

class BasePainter
{
protected:
    size_t m_width;
    size_t m_height;

public:
    BasePainter() = default;
    virtual ~BasePainter() = default;

    virtual void drawLine(const Vertex &p1, const Vertex &p2) = 0;
    virtual void drawLine(const double x1, const double y1, const double x2, const double y2) = 0;

    virtual void clear() = 0;

    virtual size_t getWidth() const noexcept = 0;
    virtual size_t getHeight() const noexcept = 0;
};
