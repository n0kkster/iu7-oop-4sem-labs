#pragma once

#include "../../products/BasePainter.h"
#include <QGraphicsScene>
#include <memory>

class QtPainter final : public BasePainter
{
private:
    std::shared_ptr<QGraphicsScene> m_scene;

public:
    QtPainter() = delete;
    QtPainter(std::shared_ptr<QGraphicsScene> scene);

    virtual ~QtPainter() override = default;

    void drawLine(const Vertex &p1, const Vertex &p2) override;
    void drawLine(const double x1, const double y1, const double x2, const double y2) override;

    void clear() override;

    size_t getWidth() const noexcept override;
    size_t getHeight() const noexcept override;
};