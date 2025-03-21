#include "draw.h"

static err_code_e drawEdge(plane_t &plane, const edge2D_t &edge)
{
    point2D_t realStart = edge.start;
    point2D_t realEnd = edge.end;

    realCoordsToScreenCoords(realStart, plane.plane_size);
    realCoordsToScreenCoords(realEnd, plane.plane_size);

    err_code_e rc = drawLine(plane.painter, realStart, realEnd);
    return rc;
}

static err_code_e drawEdges(plane_t &plane, const edgeArray_t &edges, const pointArray_t &points)
{
    if (edges.edges == nullptr)
        return ERROR_INVALID_PTR;

    if (edges.count <= 0)
        return ERROR_INVALID_EDGES_COUNT;
    
    err_code_e rc = ERROR_SUCCESS;
    edge2D_t edge;

    for (ssize_t i = 0; rc == ERROR_SUCCESS && i < edges.count; i++)
    {
        rc = projectEdge(edge, edges.edges[i], points);
        if (rc == ERROR_SUCCESS)
            rc = drawEdge(plane, edge);
    } 

    return rc;
}

static bool wireframeLoaded(const edgeArray_t &edges, const pointArray_t &points)
{
    bool res = true;
    if (edges.edges == nullptr && edges.count == 0 && points.points == nullptr && points.count == 0)
        res = false;
    
    return res;
}

err_code_e handleDraw(/* VAR */ plane_t &plane, const wireframe_t &wireframe)
{
    err_code_e rc = ERROR_SUCCESS;
    if (wireframeLoaded(wireframe.edges, wireframe.points))
        rc = drawEdges(plane, wireframe.edges, wireframe.points);
    return rc;
}
