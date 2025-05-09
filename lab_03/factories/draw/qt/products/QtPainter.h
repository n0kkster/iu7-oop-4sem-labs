#pragma once

#include "../../products/BasePainter.h"
#include "../../products/BaseScene.h"
#include <memory>

class QtPainter : public BasePainter
{
private:
    std::weak_ptr<BaseScene> m_scene;

public:
    QtPainter() = delete;
    explicit QtPainter(std::shared_ptr<BaseScene> scene);

    virtual ~QtPainter() override = default;

    void drawLine(const Vertex &p1, const Vertex &p2) override;
    void drawLine(const double x1, const double y1, const double x2, const double y2) override;
};