#pragma once

#include "../BaseStructure.h"

#include <memory>
#include <vector>

class MatrixStructure : public BaseStructure
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<std::vector<bool>> m_adjacencyMatrix;
    size_t m_vertexCount;

    void resizeMatrix(size_t newSize);

public:
    MatrixStructure();
    virtual ~MatrixStructure() override = default;

    void addVertex(const Vertex &vertex) override;
    void addEdge(const Edge &edge) override;
    void setCenter(const Vertex &vertex) noexcept override;

    std::vector<Vertex> getVertices() noexcept override;
    std::vector<Edge> getEdges() noexcept override;
    Vertex getCenter() noexcept override;

    const std::vector<Vertex> &getVertices() const noexcept override;
    const Vertex &getCenter() const noexcept override;

    void transform(std::shared_ptr<TransformAction> action) override;
};
