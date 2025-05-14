#include "DefaultProjectionStrategy.h"

void DefaultProjectionStrategy::prepare(std::shared_ptr<const BaseModel> model,
                                        std::shared_ptr<const BaseCamera> camera)
{
    m_vertices.clear();
    m_edges.clear();

    auto vertices = model->getStructure()->getVertices();
    auto edges = model->getStructure()->getEdges();
    auto transformMatrix = camera->getOrientation();

    for (const Vertex &v : vertices)
    {
        Vertex projected(v);
        projected.transform(transformMatrix);

        // TEMP TEMP TEMP
        projected.setX(projected.getX() + 430);
        projected.setY(-projected.getY() + 430);
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
