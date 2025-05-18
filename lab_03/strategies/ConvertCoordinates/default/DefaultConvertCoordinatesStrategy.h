#pragma once

#include "../BaseCoordinateConvertStrategy.h"

class DefaultConvertCoordinateStrategy : public BaseCoordinateConvertStrategy
{
public:
    DefaultConvertCoordinateStrategy() = default;
    virtual ~DefaultConvertCoordinateStrategy() override = default;

    void convertPoint(std::vector<Vertex> &vertices, const size_t width, const size_t height) override;
};