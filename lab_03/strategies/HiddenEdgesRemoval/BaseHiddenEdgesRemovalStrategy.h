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
    struct Face
    {
        std::vector<Vertex> vertices;
    };

    struct Plane
    {
        Vec3<double> normal;
        double d_coeff;

        Plane(const Vertex &pA, const Vertex &pB, const Vertex &pC)
        {
            Vec3<double> vec1 = pA - pB;
            Vec3<double> vec2 = pA - pC;
            normal = vec1.cross(vec2);
            normal = normal.normalized();
            d_coeff = -normal.dot(pA);
        }
    };

public:
    BaseHiddenEdgesRemovalStrategy() = default;
    virtual ~BaseHiddenEdgesRemovalStrategy() = default;

    virtual void prepare(const std::vector<Vertex> &vertices, const std::vector<Edge> &edges,
                         std::shared_ptr<const BaseCamera> camera, std::vector<Edge2D> &visibleEdges) = 0;
};
