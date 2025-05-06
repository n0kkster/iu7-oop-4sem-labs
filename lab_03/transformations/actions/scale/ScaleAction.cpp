#include "ScaleAction.h"

#include "../move/MoveAction.h"

ScaleAction::ScaleAction(const ScaleParams &params) : TransformAction()
{
    m_matrix[0][0] = params.getKx();
    m_matrix[1][1] = params.getKy();
    m_matrix[2][2] = params.getKz();
}

ScaleAction::ScaleAction(const double k) : TransformAction()
{
    m_matrix[0][0] = k;
    m_matrix[1][1] = k;
    m_matrix[2][2] = k;
}

ScaleAction::ScaleAction(const Vertex &vertex, const ScaleParams &params) : TransformAction()
{

    MoveAction to_center({ -vertex.getX(), -vertex.getY(), -vertex.getZ() });
    m_matrix *= to_center.getMatrix();

    ScaleAction scale(params);
    m_matrix *= scale.getMatrix();

    MoveAction from_center({ vertex.getX(), vertex.getY(), vertex.getZ() });
    m_matrix *= from_center.getMatrix();
}

ScaleAction::ScaleAction(const Vertex &vertex, const double k) : TransformAction()
{

    MoveAction to_center({ -vertex.getX(), -vertex.getY(), -vertex.getZ() });
    m_matrix *= to_center.getMatrix();

    ScaleAction scale(k);
    m_matrix *= scale.getMatrix();

    MoveAction from_center({ vertex.getX(), vertex.getY(), vertex.getZ() });
    m_matrix *= from_center.getMatrix();
}

bool ScaleAction::isMoveAction() const noexcept
{
    return false;
}
