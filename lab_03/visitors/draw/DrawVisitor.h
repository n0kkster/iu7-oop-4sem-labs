#pragma once

#include "../../factories/draw/products/BasePainter.h"
#include "../../strategies/ConvertCoordinates/BaseCoordinateConvertStrategy.h"
#include "../../strategies/HiddenEdgesRemoval/creator/HiddenEdgeRemovalStrategyCreator.h"
#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../BaseVisitor.h"

#include <memory>

class DrawVisitor : public BaseVisitor
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::shared_ptr<BaseCamera> m_camera;

    std::shared_ptr<BaseProjectionStrategy> m_projStrategy;
    std::shared_ptr<BaseHiddenEdgesRemovalStrategy> m_removalStrategy;
    std::shared_ptr<BaseCoordinateConvertStrategy> m_convertStrat;

public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrat,
                std::shared_ptr<BaseHiddenEdgesRemovalStrategy> hiddenStrat,
                std::shared_ptr<BaseCoordinateConvertStrategy> convertStrat,
                std::shared_ptr<BasePainter> painter, std::shared_ptr<BaseCamera> camera);

    void visit(BaseCamera &camera) const override;
    void visit(std::shared_ptr<BaseStructure> structure) const override;

    virtual ~DrawVisitor() override = default;
};
