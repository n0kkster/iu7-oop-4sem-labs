#include "TransformVisitor.h"

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/visible/model/structure/BaseStructure.h"

TransformVisitor::TransformVisitor(std::shared_ptr<TransformAction> action) : m_action(action) { }

void TransformVisitor::visit(BaseCamera &camera) const
{
    if (m_action)
        camera.transform(m_action);
}

void TransformVisitor::visit(std::shared_ptr<BaseStructure> structure) const
{
    if (m_action)
        structure->transform(m_action);
}

TransformVisitor::~TransformVisitor() { }
