#include "MatrixStructure.h"

#include "../../../../../../exceptions/model/ModelException.h"

MatrixStructure::MatrixStructure() : m_vertices(), m_adjacencyMatrix(), m_vertexCount(0) { }

void MatrixStructure::addVertex(const Vertex &vertex)
{
    m_vertices.push_back(vertex);
    resizeMatrix(m_vertices.size());
    m_vertexCount = m_vertices.size();
}

void MatrixStructure::addEdge(const Edge &edge)
{
    size_t id1 = edge.getStart();
    size_t id2 = edge.getEnd();

    if (id1 >= m_vertexCount || id2 >= m_vertexCount)
        throw ModelInvalidEdgeException("Edge vertex index out of range!");

    m_adjacencyMatrix[id1][id2] = true;
    m_adjacencyMatrix[id2][id1] = true;
}

void MatrixStructure::setCenter(const Vertex &vertex) noexcept
{
    m_center = vertex;
}

const std::vector<Vertex> &MatrixStructure::getVertices() const noexcept
{
    return m_vertices;
}

std::vector<Vertex> MatrixStructure::getVertices() noexcept
{
    return m_vertices;
}

std::vector<Edge> MatrixStructure::getEdges() const noexcept
{
    std::vector<Edge> edges;

    for (size_t i = 0; i < m_vertexCount; ++i)
        for (size_t j = i + 1; j < m_vertexCount; ++j)
            if (m_adjacencyMatrix[i][j])
                edges.emplace_back(i, j);

    return edges;
}

const Vertex &MatrixStructure::getCenter() const noexcept
{
    return m_center;
}

Vertex MatrixStructure::getCenter() noexcept
{
    return m_center;
}

void MatrixStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &v : m_vertices)
        action->transform(v);

    action->transform(m_center);
}

void MatrixStructure::resizeMatrix(size_t newSize)
{
    for (auto &row : m_adjacencyMatrix)
        row.resize(newSize, false);

    while (m_adjacencyMatrix.size() < newSize)
        m_adjacencyMatrix.emplace_back(newSize, false);
}
