#include "ListStructure.h"

ListStructure::ListStructure() :
    m_vertices(std::vector<Vertex>()), m_edges(std::vector<Edge>()), m_center(Vertex())
{ }

void ListStructure::addVertex(const Vertex &vertex) { this->m_vertices.push_back(vertex); }

void ListStructure::addEdge(const Edge &edge) { this->m_edges.push_back(edge); }

void ListStructure::setCenter(const Vertex &vertex) noexcept { this->m_center = vertex; }

const std::vector<Vertex> &ListStructure::getVertices() const noexcept { return this->m_vertices; }

std::vector<Vertex> ListStructure::getVertices() noexcept { return this->m_vertices; }

const std::vector<Edge> &ListStructure::getEdges() const noexcept { return this->m_edges; }

std::vector<Edge> ListStructure::getEdges() noexcept { return this->m_edges; }

const Vertex &ListStructure::getCenter() const noexcept { return this->m_center; }

Vertex ListStructure::getCenter() noexcept { return this->m_center; }

void ListStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto v : this->m_vertices)
        action->transform(v);

    action->transform(this->m_center);
}