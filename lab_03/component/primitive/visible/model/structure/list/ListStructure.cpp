#include "ListStructure.h"

ListStructure::ListStructure() : m_vertices(std::vector<Vertex>()), m_edges(std::vector<Edge>()) { }

void ListStructure::addVertex(const Vertex &vertex)
{
    m_vertices.push_back(vertex);
}

void ListStructure::addEdge(const Edge &edge)
{
    m_edges.push_back(edge);
}

void ListStructure::setCenter(const Vertex &vertex) noexcept
{
    m_center = vertex;
}

const std::vector<Vertex> &ListStructure::getVertices() const noexcept
{
    return m_vertices;
}

std::vector<Vertex> ListStructure::getVertices() noexcept
{
    return m_vertices;
}

const std::vector<Edge> &ListStructure::getEdges() const noexcept
{
    return m_edges;
}

std::vector<Edge> ListStructure::getEdges() noexcept
{
    return m_edges;
}

const Vertex &ListStructure::getCenter() const noexcept
{
    return m_center;
}

Vertex ListStructure::getCenter() noexcept
{
    return m_center;
}

void ListStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &v : m_vertices)
        action->transform(v);

    action->transform(m_center);
}
