#ifndef PLANE_H
#define PLANE_H

#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QVector>
#include <QPen>
#include <QMessageBox>

#include "wireframe.h"

class Plane : public QGraphicsView
{
    Q_OBJECT

private:
    QPointF realCoordToScreenCoord(QPointF point);

    QVector<QPointF> points;
    QVector<edge_t> edges;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit Plane(QWidget *parent = nullptr);
    void clearPoints();
    void clearEdges();
    void addPoint(QPointF point);
    void addEdge(edge_t edge);
};

#endif // PLANE_H