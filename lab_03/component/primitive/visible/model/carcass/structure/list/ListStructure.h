#pragma once

#include "../BaseStructure.h"

class ListStructure final : public BaseStructure
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;

public:
    ListStructure();
    virtual ~ListStructure() override = default;

    void addVertex(const Vertex &vertex) override;
    void addEdge(const Edge &edge) override;
    void setCenter(const Vertex &vertex) noexcept override;

    std::vector<Vertex> getVertices() noexcept override;
    std::vector<Edge> getEdges() noexcept override;
    Vertex getCenter() noexcept override;

    const std::vector<Vertex> &getVertices() const noexcept override;
    const std::vector<Edge> &getEdges() const noexcept override;
    const Vertex &getCenter() const noexcept override;

    void transform(std::shared_ptr<TransformAction> action) override;
};
