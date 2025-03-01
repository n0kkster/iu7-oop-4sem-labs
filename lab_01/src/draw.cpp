#include "draw.h"

static QPointF projectPoint(const point_t &point)
{
    QPointF projected;
    projected.setX(point.x);
    projected.setY(point.y);
    return projected;
}

static void addEdgesToCanvas(Plane *plane, const edgeArray_t &edges)
{
    for (size_t i = 0; i < edges.count; i++)
        plane->addEdge(edges.edges[i]);
}

static void addPointsToCanvas(Plane *plane, const pointArray_t &points)
{
    QPointF point;
    for (size_t i = 0; i < points.count; i++)
    {
        point = projectPoint(points.points[i]);
        plane->addPoint(point);
    }
}

void handleDraw(const draw_params_t &params, const wireframe_t &wireframe)
{
    Plane *plane = params.plane;
    plane->clearPoints();
    plane->clearEdges();

    addPointsToCanvas(plane, wireframe.points);
    addEdgesToCanvas(plane, wireframe.edges);
    plane->update();
}