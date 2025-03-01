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

// static err_code_e checkEdge(const edge_t &edge, const long pointsCount)
// {
//     err_code_e rc = ERROR_SUCCESS;
//     if (edge.id1 > pointsCount || edge.id2 > pointsCount)
//         rc = ERROR_INVALID_EDGE;
//     return rc;
// }

// static err_code_e checkEdges(const pEdgeArray_t edges, const long edgesCount, const long pointsCount)
// {
//     err_code_e rc = ERROR_SUCCESS;
//     for (long i = 0; i < edgesCount && rc == ERROR_SUCCESS; i++)
//         rc = checkEdge(edges[i], pointsCount);
//     return rc;
// }

// err_code_e checkWireframe(const wireframe_t &wireframe)
// {
//     err_code_e rc = checkEdges(wireframe.edges, wireframe.edges_count, wireframe.points_count);
//     return rc;
// }

void moveWireframe(/* OUT */ wireframe_t &dst, const wireframe_t &src)
{
    dst = src;
}

void freePoints(pointArray_t &points)
{
    free(points.points);
    points.count = 0;
}

void freeEdges(edgeArray_t &edges)
{
    free(edges.edges);
    edges.count = 0;
}

void freeWireframe(/* VAR */ wireframe_t &wireframe)
{
    freeEdges(wireframe.edges);
    freePoints(wireframe.points);
}