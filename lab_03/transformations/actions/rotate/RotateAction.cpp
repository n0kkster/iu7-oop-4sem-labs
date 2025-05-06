#include "RotateAction.h"

#include "../move/MoveAction.h"

#include <cmath>

RotateAction::RotateAction(const RotationParams &params) : TransformAction()
{

    Matrix<double> x_turn(4, 0), y_turn(4, 0), z_turn(4, 0);
    x_turn[0][0] = 1;
    x_turn[1][1] = cos(params.getAngleX());
    x_turn[1][2] = sin(params.getAngleX());
    x_turn[2][1] = -sin(params.getAngleX());
    x_turn[2][2] = cos(params.getAngleX());
    x_turn[3][3] = 1;

    y_turn[0][0] = cos(params.getAngleY());
    y_turn[0][2] = -sin(params.getAngleY());
    y_turn[1][1] = 1;
    y_turn[2][0] = sin(params.getAngleY());
    y_turn[2][2] = cos(params.getAngleY());
    y_turn[3][3] = 1;

    z_turn[0][0] = cos(params.getAngleZ());
    z_turn[0][1] = sin(params.getAngleZ());
    z_turn[1][0] = -sin(params.getAngleZ());
    z_turn[1][1] = cos(params.getAngleZ());
    z_turn[2][2] = 1;
    z_turn[3][3] = 1;

    m_matrix *= x_turn * y_turn * z_turn;
}

RotateAction::RotateAction(const Vertex &vertex, const RotationParams &params) : TransformAction()
{

    MoveAction to_center({ -vertex.getX(), -vertex.getY(), -vertex.getZ() });
    m_matrix *= to_center.getMatrix();

    RotateAction rotate(params);
    m_matrix *= rotate.getMatrix();

    MoveAction from_center({ vertex.getX(), vertex.getY(), vertex.getZ() });
    m_matrix *= from_center.getMatrix();
}

bool RotateAction::isMoveAction() const noexcept
{
    return false;
}
