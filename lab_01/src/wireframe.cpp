#include "wireframe.h"
#include "errors.h"

static err_code_e initEdges(edgeArray_t &edges)
{
    edges.edges = nullptr;
    edges.count = 0;
    return ERROR_SUCCESS;
}

static err_code_e initPoints(pointArray_t &points)
{
    points.points = nullptr;
    points.count = 0;
    return ERROR_SUCCESS;
}

wireframe_t initWireframe()
{
    wireframe_t wireframe;
    
    initPoints(wireframe.points);
    initEdges(wireframe.edges);

    return wireframe;
}

static err_code_e checkEdge(const edge_t &edge, const ssize_t pointsCount)
{
    err_code_e rc = ERROR_SUCCESS;
    if (edge.id1 >= pointsCount || edge.id2 >= pointsCount)
        rc = ERROR_INVALID_EDGE;
    return rc;
}

static err_code_e checkEdges(const edgeArray_t &edges, const pointArray_t &points)
{
    err_code_e rc = ERROR_SUCCESS;
    for (ssize_t i = 0; i < edges.count && rc == ERROR_SUCCESS; i++)
        rc = checkEdge(edges.edges[i], points.count);
    return rc;
}

err_code_e checkWireframe(const wireframe_t &wireframe)
{
    err_code_e rc = checkEdges(wireframe.edges, wireframe.points);
    return rc;
}

err_code_e moveWireframe(/* OUT */ wireframe_t &dst, const wireframe_t &src)
{
    freeWireframe(dst);
    dst = src;
    return ERROR_SUCCESS;
}

err_code_e freePoints(pointArray_t &points)
{
    free(points.points);
    points.points = nullptr;
    points.count = 0;

    return ERROR_SUCCESS;
}

err_code_e freeEdges(edgeArray_t &edges)
{
    free(edges.edges);
    edges.edges = nullptr;
    edges.count = 0;

    return ERROR_SUCCESS;
}

err_code_e freeWireframe(/* VAR */ wireframe_t &wireframe)
{
    freeEdges(wireframe.edges);
    freePoints(wireframe.points);
    
    return ERROR_SUCCESS;
}