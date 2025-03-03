#include "plane.h"

// Конструктор
// ==================================================
Plane::Plane(QWidget *parent) : QGraphicsView(parent) 
{
    handleAction(projection, {.action = INIT, .null_params = nullptr});
}
// ==================================================

void Plane::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());


    for (ssize_t i = 0; i < projection.edges.count; i++)
        painter.drawLine(realCoordToScreenCoord(projection.edges.edges[i].start), realCoordToScreenCoord(projection.edges.edges[i].end));
}

err_code_e Plane::doAction(const action_params_t &action)
{
    err_code_e rc = handleAction(projection, action);
    viewport()->update();
    return rc;
}

QPointF Plane::realCoordToScreenCoord(point2D_t point)
{
    return {point.x + viewport()->size().width() / 2, -point.y + viewport()->size().height() / 2};
}