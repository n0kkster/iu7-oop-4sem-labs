#pragma once

#include "../BaseManager.h"
#include "../../factories/draw/products/BasePainter.h"
#include <memory>

class DrawManager : public BaseManager
{
private:
    std::shared_ptr<BasePainter> m_painter;

public:
    DrawManager() = default;
    void setPainter(std::shared_ptr<BasePainter> painter);
    virtual ~DrawManager() override = default;

    void draw();
};