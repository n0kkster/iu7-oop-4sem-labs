#include "projection.h"

static void projectPoint(/* VAR */ point2D_t &projected, const point_t &point)
{
    projected.x = point.x;
    projected.y = point.y;
}

err_code_e projectEdge(/* VAR */ edge2D_t &edge2D, const edge_t &edge3D, const pointArray_t &points)
{
    if (points.points == nullptr)
        return ERROR_INVALID_PTR;
    
    if (edge3D.id1 >= points.count || edge3D.id2 >= points.count)
        return ERROR_INVALID_POINTS_COUNT;

    projectPoint(edge2D.start, points.points[edge3D.id1]);
    projectPoint(edge2D.end, points.points[edge3D.id2]);
    return ERROR_SUCCESS;
}
