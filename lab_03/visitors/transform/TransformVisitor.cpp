#include "TransformVisitor.h"

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/visible/model/carcass/CarcassModel.h"

TransformVisitor::TransformVisitor(std::shared_ptr<TransformAction> action) : m_action(action) { }

void TransformVisitor::visit(BaseCamera &camera) const
{
    if (m_action)
        camera.transform(m_action);
}

void TransformVisitor::visit(CarcassModel &model) const
{
    if (m_action)
        model.getStructure()->transform(m_action);
}
