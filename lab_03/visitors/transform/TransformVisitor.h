#pragma once

#include "../../transformations/actions/TransformAction.h"
#include "../BaseVisitor.h"

#include <memory>

class TransformVisitor : public BaseVisitor
{
protected:
    std::shared_ptr<TransformAction> m_action;

public:
    TransformVisitor() = delete;
    TransformVisitor(std::shared_ptr<TransformAction> action);
    virtual ~TransformVisitor() = 0;

    void visit(BaseCamera &camera) const override;
    void visit(std::shared_ptr<BaseStructure> structure) const override;
};
