#pragma once

#include "../BaseDrawFactory.h"

#include <memory>
#include <QGraphicsScene>

class QtDrawFactory : public BaseDrawFactory
{
private:
    std::shared_ptr<QGraphicsScene> m_scene;

public:
    QtDrawFactory() = delete;
    QtDrawFactory(std::shared_ptr<QGraphicsScene> scene);
    virtual ~QtDrawFactory() override = default;

    std::unique_ptr<BasePainter> createPainter() override;
};
