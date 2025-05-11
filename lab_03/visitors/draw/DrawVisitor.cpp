#include "DrawVisitor.h"

#include "../../component/primitive/visible/model/carcass/CarcassModel.h"

#include <memory>

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> strategy,
                         std::shared_ptr<BasePainter> painter, std::shared_ptr<BaseCamera> camera) :
    m_painter(painter), m_camera(camera), m_strategy(strategy)
{ }

void DrawVisitor::visit(CarcassModel &model) const
{
    m_strategy->prepare(std::make_shared<CarcassModel>(model), m_camera);

    const auto vertices = m_strategy->getVertices();
    const auto edges = m_strategy->getEdges();

    for (const auto edge : edges)
    {
        m_painter->drawLine(vertices[edge.getStart()], vertices[edge.getEnd()]);
    }
}

void DrawVisitor::visit(BaseCamera &model) const { }
