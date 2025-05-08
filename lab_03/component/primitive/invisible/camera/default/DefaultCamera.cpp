#include "DefaultCamera.h"
#include <memory>

DefaultCamera::DefaultCamera() : m_orientation(4, 4, 0), m_viewpoint(0, 0, 0)
{
    m_orientation[0][0] = 1;
    m_orientation[1][1] = 1;
    m_orientation[2][2] = 1;
    m_orientation[3][3] = 1;
}

DefaultCamera::DefaultCamera(const Vertex &viewpoint) : m_orientation(4, 4, 0), m_viewpoint(viewpoint)
{
    m_orientation[0][0] = 1;
    m_orientation[1][1] = 1;
    m_orientation[2][2] = 1;
    m_orientation[3][3] = 1;
}

DefaultCamera::DefaultCamera(const Vertex &viewpoint, const Matrix<double> orientation) :
    m_orientation(orientation), m_viewpoint(viewpoint)
{ }

const Matrix<double> &DefaultCamera::getOrientation() const noexcept
{
    return m_orientation;
}

void DefaultCamera::setOrientation(const Matrix<double> &orientation)
{
    m_orientation = orientation;
}

void DefaultCamera::setViewpoint(const Vertex &viewpoint) noexcept
{
    m_viewpoint = viewpoint;
}

void DefaultCamera::transform(const std::shared_ptr<const TransformAction> action)
{
    return;
}