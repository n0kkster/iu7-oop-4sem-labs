#include "QtDrawFactory.h"

#include "products/QtPainter.h"

QtDrawFactory::QtDrawFactory(std::unique_ptr<QGraphicsScene> scene) : m_scene(std::move(scene)) { }

std::unique_ptr<BasePainter> QtDrawFactory::createPainter()
{
    return std::make_unique<QtPainter>(std::move(m_scene));
}
