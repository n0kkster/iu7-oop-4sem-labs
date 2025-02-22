#include "draw.h"

void handleDraw(const draw_params_t &params, const wireframe_t &wireframe)
{
    Plane *plane = params.plane;
    plane->clearPoints();
    plane->clearEdges();

    addPointsToCanvas(plane, wireframe.points_count, wireframe.points);
    addEdgesToCanvas(plane, wireframe.edges_count, wireframe.edges);
    plane->viewport()->update();
}

void addPointsToCanvas(Plane *plane, const size_t count, const pointArray_t points)
{
    QPointF point;
    for (size_t i = 0; i < count; i++)
    {
        point = projectPoint(points[i].coord);
        plane->addPoint(point);
    }
}

void addEdgesToCanvas(Plane *plane, const size_t count, const edgeArray_t edges)
{
    for (size_t i = 0; i < count; i++)
        plane->addEdge(edges[i]);
}

QPointF projectPoint(const pointCoord_t &point)
{
    QPointF projected;
    projected.setX(point.x/*  - point.z * cos(55 * M_PI / 180.0) */);
    projected.setY(point.y/*  - point.z * sin(15 * M_PI / 180.0) */);
    return projected;
}