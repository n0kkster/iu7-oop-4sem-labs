#include "DefaultCamera.h"

#include <memory>

DefaultCamera::DefaultCamera() :
    m_viewpoint(0, 0, 500), m_up(Vec3<double>::up()), m_right(Vec3<double>::right()),
    m_forward(Vec3<double>::forward()), m_fov(90.), m_near(0.1), m_far(100.)
{ }

DefaultCamera::DefaultCamera(const Vertex &viewpoint) : m_viewpoint(viewpoint) { }

const Matrix<double> DefaultCamera::getLookMatrix() const noexcept
{
    Vec3 forward = m_forward.normalized();
    Vec3 right = m_forward.cross(m_up).normalized();
    Vec3 realUp = right.cross(forward);

    Matrix<double> lookMatrix(4, 4, 0);

    lookMatrix[0][0] = right.getX();
    lookMatrix[1][0] = right.getY();
    lookMatrix[2][0] = right.getZ();

    lookMatrix[0][1] = realUp.getX();
    lookMatrix[1][1] = realUp.getY();
    lookMatrix[2][1] = realUp.getZ();

    lookMatrix[0][2] = -forward.getX();
    lookMatrix[1][2] = -forward.getY();
    lookMatrix[2][2] = -forward.getZ();

    lookMatrix[0][3] = -(right.dot(m_viewpoint));
    lookMatrix[1][3] = -(realUp.dot(m_viewpoint));
    lookMatrix[2][3] = (forward.dot(m_viewpoint));

    return lookMatrix;
}

const Matrix<double> DefaultCamera::getProjectionMatrix(double aspectRatio) const
{
    Matrix<double> projMatrix(4, 4, 0.0);

    double fovRad = m_fov * M_PI / 180.0;
    double tanHalfFov = tan(fovRad / 2.0);

    projMatrix[0][0] = 1.0 / (aspectRatio * tanHalfFov);
    projMatrix[1][1] = 1.0 / tanHalfFov;
    projMatrix[2][2] = -(m_far + m_near) / (m_far - m_near);
    projMatrix[2][3] = -2.0 * m_far * m_near / (m_far - m_near);
    projMatrix[3][2] = -1.0;

    return projMatrix;
}

Vertex DefaultCamera::getCenter() const noexcept
{
    return m_viewpoint;
}

void DefaultCamera::transform(const std::shared_ptr<const TransformAction> action)
{
    if (action->isMoveAction())
        action->transform(m_viewpoint);
    else
    {
        const auto &transformMatrix = action->getMatrix();

        Matrix<double> rotationPart(3, 3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                rotationPart[i][j] = transformMatrix[i][j];

        m_forward = (rotationPart * m_forward).normalized();
        m_right = (rotationPart * m_right).normalized();
        m_up = (rotationPart * m_up).normalized();

        m_right = m_forward.cross(m_up).normalized();
        m_up = m_right.cross(m_forward).normalized();
    }
}

void DefaultCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(*this);
}
