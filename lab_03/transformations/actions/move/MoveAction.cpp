#include "MoveAction.h"

MoveAction::MoveAction(const MoveParams &params) noexcept : TransformAction()
{
    m_matrix[3][0] = params.getOffsetX();
    m_matrix[3][1] = params.getOffsetY();
    m_matrix[3][2] = params.getOffsetZ();
}

bool MoveAction::isMoveAction() const noexcept
{
    return true;
}
