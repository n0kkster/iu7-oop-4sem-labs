#pragma once

#include "../BaseDrawFactory.h"

#include <memory>
#include <QGraphicsScene>

class QtDrawFactory : public BaseDrawFactory
{
private:
    std::unique_ptr<QGraphicsScene> m_scene;

public:
    QtDrawFactory() = delete;
    QtDrawFactory(std::unique_ptr<QGraphicsScene> scene);
    virtual ~QtDrawFactory() override = default;

    std::unique_ptr<BasePainter> createPainter() override;
};
