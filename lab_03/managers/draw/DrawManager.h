#pragma once

#include "../BaseManager.h"
#include "../../factories/draw/products/BasePainter.h"
#include <memory>

class DrawManager : public BaseManager
{
private:
    std::unique_ptr<BasePainter> m_painter;

public:
    DrawManager() = default;
    void setPainter(std::unique_ptr<BasePainter> painter);
    virtual ~DrawManager() override = default;

    void draw();
};