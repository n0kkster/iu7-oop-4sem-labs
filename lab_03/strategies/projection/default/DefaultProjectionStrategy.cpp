#include "DefaultProjectionStrategy.h"

void DefaultProjectionStrategy::prepare(std::shared_ptr<const BaseModel> model,
                                        std::shared_ptr<const BaseCamera> camera, const size_t width,
                                        const size_t height)
{
    m_vertices.clear();
    m_edges.clear();

    const auto &vertices = model->getStructure()->getVertices();
    const auto &edges = model->getStructure()->getEdges();
    const auto &lookMatrix = camera->getLookMatrix();
    const auto &projectionMatrix = camera->getProjectionMatrix(1.0);
    const auto transformMatrix = projectionMatrix * lookMatrix;

    size_t centerX = static_cast<size_t>(width / 2);
    size_t centerY = static_cast<size_t>(height / 2);

    for (const Vertex &v : vertices)
    {
        Vertex projected(v);
        projected.transform(transformMatrix);

        double w = projected.getW();
        if (w != 0.0)
        {
            projected.setX(projected.getX() / w);
            projected.setY(projected.getY() / w);
            projected.setZ(projected.getZ() / w);
        }

        projected.setX(projected.getX() * centerX + centerX);
        projected.setY(-projected.getY() * centerY + centerY);

        m_vertices.push_back(projected);
    }

    m_edges = edges;
}

const std::vector<Vertex> DefaultProjectionStrategy::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<Edge> DefaultProjectionStrategy::getEdges() const noexcept
{
    return m_edges;
}
