#include "DefaultProjectionStrategy.h"

void DefaultProjectionStrategy::prepare(std::shared_ptr<const BaseModel> model,
                                        std::shared_ptr<const BaseCamera> camera)
{
    m_vertices.clear();
    m_edges.clear();

    const auto &vertices = model->getStructure()->getVertices();
    const auto &edges = model->getStructure()->getEdges();
    const auto &lookMatrix = camera->getLookMatrix();
    const auto &projectionMatrix = camera->getProjectionMatrix(1.0);
    const auto transformMatrix = projectionMatrix * lookMatrix;

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

        // TEMP TEMP TEMP
        projected.setX(projected.getX() * 430 + 430);
        projected.setY(-projected.getY() * 430 + 430);
        // TEMP TEMP TEMP

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
