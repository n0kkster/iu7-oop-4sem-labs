#include "MoveAction.h"

MoveAction::MoveAction(const MoveParams &params) noexcept : TransformAction()
{
    m_matrix[0][3] = params.getOffsetX();
    m_matrix[1][3] = params.getOffsetY();
    m_matrix[2][3] = params.getOffsetZ();
}

bool MoveAction::isMoveAction() const noexcept
{
    return true;
}
