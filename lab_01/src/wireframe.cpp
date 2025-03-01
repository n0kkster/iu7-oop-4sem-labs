#include "wireframe.h"
#include "errors.h"

wireframe_t initWireframe()
{
    wireframe_t wireframe;
    
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    wireframe.edges = nullptr;
    wireframe.points = nullptr;

    return wireframe;
}

static err_code_e checkEdge(const edge_t &edge, const long pointsCount)
{
    err_code_e rc = ERROR_SUCCESS;
    if (edge.id1 > pointsCount || edge.id2 > pointsCount)
        rc = ERROR_INVALID_EDGE;
    return rc;
}

err_code_e checkEdges(const pEdgeArray_t edges, const long edgesCount, const long pointsCount)
{
    err_code_e rc = ERROR_SUCCESS;
    for (long i = 0; i < edgesCount && rc == ERROR_SUCCESS; i++)
        rc = checkEdge(edges[i], pointsCount);
    return rc;
}

void copyWireframe(/* OUT */ wireframe_t &dst, const wireframe_t &src)
{
    dst = src;
}

static void freePoints(const pPointArray_t points)
{
    free(points);
}

static void freeEdges(const pEdgeArray_t edges)
{
    free(edges);
}

void freeWireframe(/* VAR */ wireframe_t &wireframe)
{
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    freeEdges(wireframe.edges);
    freePoints(wireframe.points);
}