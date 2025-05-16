#include "QtPainter.h"

QtPainter::QtPainter(std::shared_ptr<QGraphicsScene> scene) :
    m_scene(scene)
{ 
    m_width = m_scene->width();
    m_height = m_scene->height();
}

void QtPainter::drawLine(const Vertex &p1, const Vertex &p2)
{
    m_scene->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), { Qt::white });
}

void QtPainter::drawLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene->addLine(x1, y1, x2, y2, { Qt::white });
}

void QtPainter::clear()
{
    m_scene->clear();
}

size_t QtPainter::getWidth() const noexcept
{
    return m_width;
}

size_t QtPainter::getHeight() const noexcept
{
    return m_height;
}
