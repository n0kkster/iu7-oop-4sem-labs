#include "plane.h"

// Конструктор
// ==================================================
Plane::Plane(QWidget *parent) : QGraphicsView(parent) {}
// ==================================================

void Plane::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());

    // for (const auto &p : points)
        // painter.drawPoint(realCoordToScreenCoord(p));
    
    for (const auto &e : edges)
        painter.drawLine(realCoordToScreenCoord(points[e.id1]), realCoordToScreenCoord(points[e.id2]));
}

QPointF Plane::realCoordToScreenCoord(QPointF point)
{
    return {point.x() + viewport()->size().width() / 2, -point.y() + viewport()->size().height() / 2};
}

void Plane::clearPoints()
{
    points.clear();
}

void Plane::clearEdges()
{
    edges.clear();
}

void Plane::update()
{
    viewport()->update();
}

void Plane::addPoint(QPointF point)
{
    points.append(point);
}

void Plane::addEdge(edge_t edge)
{
    edges.append(edge);
}