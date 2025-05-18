#include "DrawVisitor.h"

#include <memory>

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrat,
                         std::shared_ptr<BaseHiddenEdgesRemovalStrategy> removalStrat,
                         std::shared_ptr<BaseCoordinateConvertStrategy> convertStrat,
                         std::shared_ptr<BasePainter> painter, std::shared_ptr<BaseCamera> camera) :
    m_painter(painter), m_camera(camera), m_projStrategy(projStrat), m_removalStrategy(removalStrat),
    m_convertStrat(convertStrat)
{ }

void DrawVisitor::visit(std::shared_ptr<BaseStructure> structure) const
{
    std::vector<Vertex> projected;
    m_projStrategy->project(structure, m_camera, projected);

    m_convertStrat->convertPoint(projected, m_painter->getWidth(), m_painter->getHeight());

    std::vector<BaseHiddenEdgesRemovalStrategy::Edge2D> visibleEdges;
    m_removalStrategy->prepare(projected, structure->getEdges(), m_camera, visibleEdges);

    for (const auto &e : visibleEdges)
        m_painter->drawLine(e.first, e.second);
}

void DrawVisitor::visit(BaseCamera &camera) const { (void)camera; }
