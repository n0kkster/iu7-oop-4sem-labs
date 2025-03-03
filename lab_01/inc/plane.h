#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QVector>
#include <QPen>
#include <QMessageBox>

#include "projection.h"
#include "errors.h"
#include "handler.h"

class Plane : public QGraphicsView
{
    Q_OBJECT

private:
    QPointF realCoordToScreenCoord(point2D_t point);
    projection_t projection;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit Plane(QWidget *parent = nullptr);
    err_code_e doAction(const action_params_t &action);
};

#endif /* PLANE_H */
