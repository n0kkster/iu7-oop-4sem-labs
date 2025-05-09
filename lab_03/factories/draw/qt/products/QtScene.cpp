#include "QtScene.h"

QtScene::QtScene(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene) { };

void QtScene::addLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene->addLine(x1, y1, x2, y2);
}

void QtScene::addLine(const Vertex &p1, const Vertex &p2)
{
    m_scene->addLine(p1.getX(), p1.getY(), p2.getY(), p2.getY());
}