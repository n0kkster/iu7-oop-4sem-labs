#pragma once

#include "../../component/primitive/visible/model/vertex/Vertex.h"

#include <vector>

class BaseCoordinateConvertStrategy
{
public:
    BaseCoordinateConvertStrategy() = default;
    virtual ~BaseCoordinateConvertStrategy() = default;

    virtual void convertPoint(std::vector<Vertex> &vertices, const size_t width, const size_t height) = 0;
};
