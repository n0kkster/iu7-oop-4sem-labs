#include "ScaleAction.h"

#include "../move/MoveAction.h"

ScaleAction::ScaleAction(const ScaleParams &params) : TransformAction()
{

    MoveAction to_center({ -params.getCx(), -params.getCy(), -params.getCz() });
    m_matrix *= to_center.getMatrix();

    Matrix<double> scaleMatrix(4, 4, 0);
    scaleMatrix[0][0] = params.getKx();
    scaleMatrix[1][1] = params.getKy();
    scaleMatrix[2][2] = params.getKz();

    m_matrix *= scaleMatrix;

    MoveAction from_center({ params.getCx(), params.getCy(), params.getCz() });
    m_matrix *= from_center.getMatrix();
}

bool ScaleAction::isMoveAction() const noexcept
{
    return false;
}
