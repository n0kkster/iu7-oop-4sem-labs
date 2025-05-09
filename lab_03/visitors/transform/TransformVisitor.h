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
    virtual ~TransformVisitor() override = default;

    void visit(BaseCamera &camera) const override;
    void visit(CarcassModel &model) const override;
};
