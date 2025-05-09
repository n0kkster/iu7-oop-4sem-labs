#include "QtPainter.h"

QtPainter::QtPainter(std::shared_ptr<BaseScene> scene) : m_scene(scene) { }

void QtPainter::drawLine(const Vertex &p1, const Vertex &p2)
{
    m_scene.lock()->addLine(p1, p2);
}

void QtPainter::drawLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene.lock()->addLine(x1, y1, x2, y2);
}
