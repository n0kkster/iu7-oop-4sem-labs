#include "MoveAction.h"

#include <iostream>

MoveAction::MoveAction(const MoveParams &params) noexcept : TransformAction()
{
    std::cout << "called MoveAction() ctor. x: " << params.getOffsetX() << " y: " << params.getOffsetY()
              << " z: " << params.getOffsetZ() << std::endl;
    m_matrix[0][3] = params.getOffsetX();
    m_matrix[1][3] = params.getOffsetY();
    m_matrix[2][3] = params.getOffsetZ();
}

bool MoveAction::isMoveAction() const noexcept
{
    return true;
}
