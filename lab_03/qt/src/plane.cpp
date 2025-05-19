#include "plane.h"

#include "../../commands/BaseCommand.h"
#include "../../commands/camera/CameraCommand.h"
#include "../../commands/scene/SceneCommand.h"

#include <QDebug>

Plane::Plane(QWidget *parent) : QGraphicsView(parent) { }

void Plane::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(viewport());
}

void Plane::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug() << "mouse pressed!";
    m_pressStarted = event->pos();
}

void Plane::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug() << "mouse release!";
}

void Plane::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    auto offset = event->pos() - m_pressStarted;
    // qDebug() << "start: " << m_pressStarted << "offset: " << offset;
    RotationParams params = { -qDegreesToRadians(static_cast<double>(offset.y()) / 2),
                              -qDegreesToRadians(static_cast<double>(offset.x()) / 2),
                              0,
                              0,
                              0,
                              0 };

    std::shared_ptr<BaseCommand> rotateCameraCommand = std::make_shared<RotateCameraCommand>(0, params);
    m_facade.execute(rotateCameraCommand);

    std::shared_ptr<BaseCommand> drawCommand = std::make_shared<DrawSceneCommand>();
    m_facade.execute(drawCommand);

    m_pressStarted = event->pos();
}
