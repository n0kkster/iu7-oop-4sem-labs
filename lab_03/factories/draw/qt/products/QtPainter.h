#pragma once

#include "../../products/BasePainter.h"
#include <QGraphicsScene>
#include <memory>

class QtPainter : public BasePainter
{
private:
    std::unique_ptr<QGraphicsScene> m_scene;

public:
    QtPainter() = delete;
    explicit QtPainter(std::unique_ptr<QGraphicsScene> scene);

    virtual ~QtPainter() override = default;

    void drawLine(const Vertex &p1, const Vertex &p2) override;
    void drawLine(const double x1, const double y1, const double x2, const double y2) override;

    void clear() override;
};