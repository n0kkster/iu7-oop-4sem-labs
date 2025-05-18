#include "RaycastingHiddenEdgesRemoval.h"

void RaycastingHiddenEdgesRemovalStrategy::prepare(const std::vector<Vertex> &vertices,
                                                   const std::vector<Edge> &edges,
                                                   std::shared_ptr<const BaseCamera> camera,
                                                   std::vector<Edge2D> &visibleEdges)
{
    findFaces(vertices, edges);

    double t1, t2;
    bool startVisible = true, endVisible = true;

    auto viewpoint = camera->getCenter();

    viewpoint.setX(viewpoint.getX() + 430);
    viewpoint.setY(-viewpoint.getY() + 415);
    viewpoint.setZ(-(viewpoint.getY() * 20));

    for (const auto &edge : edges)
    {
        auto start = vertices[edge.getStart()];
        auto end = vertices[edge.getEnd()];

        start.setZ(start.getZ() * start.getW());
        end.setZ(end.getZ() * end.getW());

        startVisible = true;
        endVisible = true;

        for (const auto &face : m_faces)
        {
            if (std::ranges::find(face.vertices, start) == face.vertices.end())
            {
                auto i1 = intersectLineWithPlane(viewpoint, start, face, t1);
                if (i1 && t1 < 0 && (std::abs(t1) > 0 && std::abs(t1) < 1))
                    if (isPointInPolygon(i1.value(), face))
                        startVisible = false;
            }

            if (std::ranges::find(face.vertices, end) == face.vertices.end())
            {
                auto i2 = intersectLineWithPlane(viewpoint, end, face, t2);
                if (i2 && t2 < 0 && (std::abs(t2) > 0 && std::abs(t2) < 1))
                    if (isPointInPolygon(i2.value(), face))
                        endVisible = false;
            }
        }
        if (startVisible && endVisible)
            visibleEdges.push_back({ start, end });
    }
}

void RaycastingHiddenEdgesRemovalStrategy::findFaces(const std::vector<Vertex> &vertices,
                                                     const std::vector<Edge> &edges)
{
    m_faces.clear();

    std::map<int, std::vector<int>> adj;
    for (const auto &edge : edges)
    {
        adj[edge.getStart()].push_back(edge.getEnd());
        adj[edge.getEnd()].push_back(edge.getStart());
    }

    for (auto &pair : adj)
        std::sort(pair.second.begin(), pair.second.end());

    std::vector<std::vector<int>> processed_faces;

    for (const auto &edge : edges)
    {
        int v1_idx = edge.getStart();
        int v2_idx = edge.getEnd();

        for (int v3_idx : adj[v2_idx])
        {
            if (v3_idx == v1_idx)
                continue;

            for (int v4_idx : adj[v3_idx])
            {
                if (v4_idx == v2_idx || v4_idx == v1_idx)
                    continue;

                if (std::binary_search(adj[v4_idx].begin(), adj[v4_idx].end(), v1_idx))
                {
                    std::vector<int> face_ids = { v1_idx, v2_idx, v3_idx, v4_idx };
                    std::sort(face_ids.begin(), face_ids.end());

                    bool is_new = true;
                    for (const auto &processed : processed_faces)
                    {
                        if (processed == face_ids)
                        {
                            is_new = false;
                            break;
                        }
                    }

                    if (is_new)
                    {
                        processed_faces.push_back(face_ids);

                        Face face;
                        face.vertices = { vertices[v1_idx], vertices[v2_idx], vertices[v3_idx],
                                          vertices[v4_idx] };
                        m_faces.push_back(face);
                    }
                }
            }
        }
    }

    for (auto &face : m_faces)
        for (auto &v : face.vertices)
            v.setZ(v.getZ() * v.getW());
}

std::optional<Vertex> RaycastingHiddenEdgesRemovalStrategy::intersectLineWithPlane(const Vertex &line_p1,
                                                                                   const Vertex &line_p2,
                                                                                   const Plane &plane,
                                                                                   double &out_param_t)
{
    const double epsilon = 1e-9;

    Vec3<double> line_dir = line_p1 - line_p2;

    double dot_N_Dir = plane.normal.dot(line_dir);

    if (std::abs(dot_N_Dir) < epsilon)
    {
        double val_P1_in_PlaneEq = plane.normal.dot(line_p1) + plane.d_coeff;
        if (std::abs(val_P1_in_PlaneEq) < epsilon)
        {
            out_param_t = 0.0;
            return std::nullopt;
        }
        else
            return std::nullopt;
    }

    double val_P1_in_PlaneEq = plane.normal.dot(line_p1) + plane.d_coeff;
    out_param_t = -val_P1_in_PlaneEq / dot_N_Dir;

    Vertex intersection_point;
    intersection_point.setX(line_p1.getX() + out_param_t * line_dir.getX());
    intersection_point.setY(line_p1.getY() + out_param_t * line_dir.getY());
    intersection_point.setZ(line_p1.getZ() + out_param_t * line_dir.getZ());

    return intersection_point;
}

std::optional<Vertex> RaycastingHiddenEdgesRemovalStrategy::intersectLineWithPlane(const Vertex &line_p1,
                                                                                   const Vertex &line_p2,
                                                                                   const Face &f,
                                                                                   double &out_param_t)
{
    Plane p(f.vertices[0], f.vertices[1], f.vertices[2]);
    return intersectLineWithPlane(line_p1, line_p2, p, out_param_t);
}

bool RaycastingHiddenEdgesRemovalStrategy::isPointInPolygon(const Vertex &point, const Face &f)
{
    int crossings = 0;
    double px = point.getX();
    double py = point.getY();

    for (size_t i = 0, j = f.vertices.size() - 1; i < f.vertices.size(); j = i++)
    {
        const Vertex &p_i = f.vertices[i];
        const Vertex &p_j = f.vertices[j];

        double p_i_x = p_i.getX();
        double p_i_y = p_i.getY();
        double p_j_x = p_j.getX();
        double p_j_y = p_j.getY();

        if (((p_i_y <= py && py < p_j_y) || (p_j_y <= py && py < p_i_y)))
        {

            double x_intersection = (p_j_x - p_i_x) * (py - p_i_y) / (p_j_y - p_i_y) + p_i_x;

            if (px < x_intersection)
                crossings++;
        }
    }
    return (crossings % 2) == 1;
}
