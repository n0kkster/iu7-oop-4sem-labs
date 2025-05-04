#include "TransformAction.h"

TransformAction::TransformAction() : m_matrix(4, 0)
{
    m_matrix[0][0] = 1.;
    m_matrix[1][1] = 1.;
    m_matrix[2][2] = 1.;
    m_matrix[3][3] = 1.;
}

Matrix<double> &TransformAction::getMatrix() noexcept
{
    return m_matrix;
}

const Matrix<double> &TransformAction::getMatrix() const noexcept
{
    return m_matrix;
}

Vertex &TransformAction::transform(Vertex &vertex) const noexcept
{
    vertex.transform(m_matrix);
    return vertex;
}