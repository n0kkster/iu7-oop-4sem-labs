#pragma once

#include "../BaseHiddenEdgesRemovalStrategy.h"

struct Plane;

class RaycastingHiddenEdgesRemovalStrategy : public BaseHiddenEdgesRemovalStrategy
{
private:
    std::vector<Face> m_faces;
    void createFace(const Vertex &p1, const Vertex &p2, const Vertex &p3, const Vertex &p4);
    void calculateFaces(const std::vector<Vertex> &points);
    bool arePointsCoplanar(const Vertex &a, const Vertex &b, const Vertex &c, const Vertex &d);
    std::optional<Vertex> intersectLineWithPlane(const Vertex &line_p1, const Vertex &line_p2,
                                                 const Plane &plane, double &out_param_t);
    std::optional<Vertex> intersectLineWithPlane(const Vertex &line_p1, const Vertex &line_p2, const Face &f,
                                                 double &out_param_t);
    bool isPointInPolygon(const Vertex &point, const Face &f);

    void findFaces(const std::vector<Vertex> &vertices, const std::vector<Edge> &edges);

public:
    RaycastingHiddenEdgesRemovalStrategy() = default;
    virtual ~RaycastingHiddenEdgesRemovalStrategy() override = default;

    void prepare(const std::vector<Vertex> &vertices, const std::vector<Edge> &edges,
                 std::shared_ptr<const BaseCamera> camera, std::vector<Edge2D> &visibleEdges) override;
};
