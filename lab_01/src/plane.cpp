#include "plane.h"

// Конструктор
// ==================================================
Plane::Plane(QWidget *parent) : QGraphicsView(parent) {}
// ==================================================

void Plane::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());

    plane_t plane;
    plane.painter = {&painter};
    plane.plane_size = {(size_t)viewport()->height(), (size_t)viewport()->height()};

    err_code_e rc = handleAction(plane, {.action = DRAW, .null_params = nullptr});
    if (rc != ERROR_SUCCESS)
        handleError(rc);
}

err_code_e Plane::doAction(const action_params_t &action)
{
    plane_t filler = {{nullptr}, {0, 0}};
    err_code_e rc = handleAction(filler, action);
    viewport()->update();
    return rc;
}
