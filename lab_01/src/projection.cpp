#include "projection.h"

static point2D_t projectPoint(const point_t &point)
{
    point2D_t projected;
    projected.x = point.x;
    projected.y = point.y;
    return projected;
}

static err_code_e initEdges2D(/* OUT */ edge2DArray_t &edges)
{
    edges.count = 0;
    edges.edges = nullptr;
    return ERROR_SUCCESS;
}

err_code_e initProjection(/* OUT */ projection_t &projection)
{
    err_code_e rc = initEdges2D(projection.edges);
    return rc;
}

static err_code_e freeEdges2D(/* VAR */ edge2DArray_t &edges)
{
    free(edges.edges);
    edges.count = 0;
    return ERROR_SUCCESS;
}

err_code_e freeProjection(/* VAR */ projection_t &projection)
{
    err_code_e rc = freeEdges2D(projection.edges);
    return rc;
}

static void projectEdge(/* VAR */ edge2D_t &edge2D, const edge_t &edge3D, const pPoints_t &points)
{
    edge2D.start = projectPoint(points[edge3D.id1]);
    edge2D.end = projectPoint(points[edge3D.id2]);
}

static void updateEdges(/* VAR */ edge2DArray_t &edges2D, const edgeArray_t &edges3D, const pointArray_t &points)
{
    for (ssize_t i = 0; i < edges3D.count; i++)
        projectEdge(edges2D.edges[i], edges3D.edges[i], points.points);
}

static err_code_e createEdges(/* OUT */ edge2DArray_t &edges2D, const edgeArray_t &edges3D)
{
    if (edges3D.count == 0)
        return ERROR_INVALID_EDGES_COUNT;

    if (edges3D.edges == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    edges2D.edges = (pEdge2D_t)malloc(sizeof(edge2D_t) * edges3D.count);
    if (edges2D.edges == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
        edges2D.count = edges3D.count;

    return rc;
}

err_code_e updateProjection(/* VAR */ projection_t &projection, const wireframe_t &wireframe)
{
    updateEdges(projection.edges, wireframe.edges, wireframe.points);
    return ERROR_SUCCESS;
}

err_code_e createProjection(/* OUT */ projection_t &projection, const wireframe_t &wireframe)
{
    err_code_e rc = createEdges(projection.edges, wireframe.edges);
    if (rc == ERROR_SUCCESS)
        updateEdges(projection.edges, wireframe.edges, wireframe.points);
    return rc;
}