#include "RotateAction.h"

#include "../move/MoveAction.h"

#include <cmath>

RotateAction::RotateAction(const RotationParams &params) : TransformAction()
{

    MoveAction to_center({ params.getCenterX(), params.getCenterY(), params.getCenterZ() });
    m_matrix *= to_center.getMatrix();

    Matrix<double> rotationMatrix = createRotationZ(params.getAngleZ()) * createRotationY(params.getAngleY())
                                  * createRotationX(params.getAngleX());

    m_matrix *= rotationMatrix;

    MoveAction from_center({ -params.getCenterX(), -params.getCenterY(), -params.getCenterZ() });
    m_matrix *= from_center.getMatrix();
}

Matrix<double> RotateAction::createRotationX(const double angle)
{
    Matrix<double> tMatrix(4, 4, 0);
    tMatrix[0][0] = 1;
    tMatrix[1][1] = cos(angle);
    tMatrix[1][2] = sin(angle);
    tMatrix[2][1] = -sin(angle);
    tMatrix[2][2] = cos(angle);
    tMatrix[3][3] = 1;

    return tMatrix;
}

Matrix<double> RotateAction::createRotationY(const double angle)
{
    Matrix<double> tMatrix(4, 4, 0);
    tMatrix[0][0] = cos(angle);
    tMatrix[0][2] = -sin(angle);
    tMatrix[1][1] = 1;
    tMatrix[2][0] = sin(angle);
    tMatrix[2][2] = cos(angle);
    tMatrix[3][3] = 1;

    return tMatrix;
}

Matrix<double> RotateAction::createRotationZ(const double angle)
{
    Matrix<double> tMatrix(4, 4, 0);
    tMatrix[0][0] = cos(angle);
    tMatrix[0][1] = sin(angle);
    tMatrix[1][0] = -sin(angle);
    tMatrix[1][1] = cos(angle);
    tMatrix[2][2] = 1;
    tMatrix[3][3] = 1;

    return tMatrix;
}

bool RotateAction::isMoveAction() const noexcept
{
    return false;
}
