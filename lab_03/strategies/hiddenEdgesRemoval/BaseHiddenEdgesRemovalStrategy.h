#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/visible/model/BaseModel.h"
#include "../../component/primitive/visible/model/vertex/Vertex.h"

#include <memory>
#include <utility>

class BaseHiddenEdgesRemovalStrategy
{
public:
    using Edge2D = std::pair<Vertex, Vertex>;

protected:
    std::vector<Edge2D> m_visibleEdges;

    struct Face
    {
        std::array<Vertex, 4> vertices;
    };

public:
    BaseHiddenEdgesRemovalStrategy() = default;
    virtual ~BaseHiddenEdgesRemovalStrategy() = default;

    virtual void prepare(const std::vector<Vertex> &vertices, const std::vector<Edge> &edges,
                         std::shared_ptr<const BaseCamera> camera) = 0;

    virtual std::vector<Edge2D> getVisibleEdges() = 0;
};
