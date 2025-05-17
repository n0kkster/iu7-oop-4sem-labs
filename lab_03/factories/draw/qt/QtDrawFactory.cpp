#include "QtDrawFactory.h"

#include "products/QtPainter.h"

QtDrawFactory::QtDrawFactory(std::shared_ptr<QGraphicsScene> scene) : m_scene(scene) { }

std::unique_ptr<BasePainter> QtDrawFactory::createPainter()
{
    return std::make_unique<QtPainter>(m_scene.lock());
}
