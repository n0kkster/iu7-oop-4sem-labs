#pragma once

#include "products/BasePainter.h"

#include <memory>

class BaseDrawFactory
{
public:
    BaseDrawFactory() = default;
    virtual ~BaseDrawFactory() = default;

    virtual std::unique_ptr<BasePainter> createPainter() = 0;
};
