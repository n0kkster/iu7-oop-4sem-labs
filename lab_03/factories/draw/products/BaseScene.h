#pragma once

#include "../../../component/primitive/visible/model/vertex/vertex.h"

class BaseScene
{
public:
    BaseScene() = default;
    virtual ~BaseScene() = default;

    virtual void addLine(const Vertex &p1, const Vertex &p2) = 0;
    virtual void addLine(const double x1, const double y1, const double x2, const double y2) = 0;

    virtual void clear() = 0;
};
