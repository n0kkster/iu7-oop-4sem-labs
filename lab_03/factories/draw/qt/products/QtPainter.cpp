#include "QtPainter.h"

QtPainter::QtPainter(std::unique_ptr<QGraphicsScene> scene) : m_scene(std::move(scene)) { }

void QtPainter::drawLine(const Vertex &p1, const Vertex &p2)
{
    m_scene->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void QtPainter::drawLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene->addLine(x1, y1, x2, y2);
}
