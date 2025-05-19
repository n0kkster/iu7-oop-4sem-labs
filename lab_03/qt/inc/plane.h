#ifndef PLANE_H
#define PLANE_H

#include "../../facade/Facade.h"

#include <QGraphicsView>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>

class Plane : public QGraphicsView
{
    Q_OBJECT

private:
    QPoint m_pressStarted;
    Facade m_facade;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    explicit Plane(QWidget *parent = nullptr);

    void setFacade(Facade &f) { m_facade = f; }
};

#endif /* PLANE_H */
