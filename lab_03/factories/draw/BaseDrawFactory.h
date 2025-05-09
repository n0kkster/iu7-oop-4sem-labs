#pragma once

#include "products/BasePainter.h"

#include <memory>

class BaseDrawFactory
{
public:
    BaseDrawFactory() = default;
    virtual ~BaseDrawFactory() = default;

    virtual std::shared_ptr<BasePainter> createPainter() = 0;
};
