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

void copyWireframe(/* OUT */ wireframe_t &dst, const wireframe_t &src)
{
    dst = src;
}

static void freePoints(pointArray_t points)
{
    free(points);
}

static void freeEdges(edgeArray_t edges)
{
    free(edges);
}

void freeWireframe(wireframe_t &wireframe)
{
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    freeEdges(wireframe.edges);
    freePoints(wireframe.points);
}