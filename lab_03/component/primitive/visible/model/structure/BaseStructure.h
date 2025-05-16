#pragma once

#include "../../../../../transformations/actions/TransformAction.h"
#include "../edge/Edge.h"
#include "../vertex/Vertex.h"

#include <memory>
#include <vector>

class BaseStructure
{
protected:
    Vertex m_center;

public:
    BaseStructure() = default;
    virtual ~BaseStructure() = default;

    virtual void addVertex(const Vertex &vertex) = 0;
    virtual void addEdge(const Edge &edge) = 0;
    virtual void setCenter(const Vertex &vertex) noexcept = 0;

    virtual void transform(std::shared_ptr<TransformAction> action) = 0;

    virtual std::vector<Vertex> getVertices() noexcept = 0;
    virtual std::vector<Edge> getEdges() noexcept = 0;
    virtual Vertex getCenter() noexcept = 0;

    virtual const std::vector<Vertex> &getVertices() const noexcept = 0;
    virtual const Vertex &getCenter() const noexcept = 0;
};
