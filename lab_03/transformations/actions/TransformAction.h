#pragma once

#include "../../component/primitive/visible/model/vertex/Vertex.h"
#include "../../matrix/matrix.h"

class TransformAction
{
protected:
    Matrix<double> m_matrix;

public:
    TransformAction();
    virtual ~TransformAction() = default;

    Vertex &transform(Vertex &vertex) const noexcept;
    virtual bool isMoveAction() const noexcept = 0;

    Matrix<double> &getMatrix() noexcept;
    const Matrix<double> &getMatrix() const noexcept;
};
