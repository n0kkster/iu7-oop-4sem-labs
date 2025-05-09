#pragma once

#include "../../factories/draw/products/BasePainter.h"

#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../BaseVisitor.h"

#include <memory>

class DrawVisitor : public BaseVisitor
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::shared_ptr<BaseCamera> m_camera;
    std::shared_ptr<BaseProjectionStrategy> m_strategy;

public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjectionStrategy> strategy, std::shared_ptr<BasePainter> painter,
                std::shared_ptr<BaseCamera> camera);

    void visit(BaseCamera &camera) const override;
    void visit(CarcassModel &model) const override;

    virtual ~DrawVisitor() override = default;
};
