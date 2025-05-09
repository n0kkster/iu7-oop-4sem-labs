#pragma once

#include "products/BasePainter.h"
#include "products/BaseScene.h"

#include <memory>

class BaseDrawerFactory
{
public:
    BaseDrawerFactory() = default;
    virtual ~BaseDrawerFactory() = default;

    virtual std::unique_ptr<BaseScene> createScene() = 0;
    virtual std::unique_ptr<BasePainter> createPainter() = 0;
};
