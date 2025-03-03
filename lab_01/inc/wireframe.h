#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <cstdio>
#include <cstdlib>
#include "errors.h"

typedef struct
{
    double x, y, z;
} point_t;
typedef point_t* pPoints_t;

typedef struct
{
    pPoints_t points;
    ssize_t count;
} pointArray_t;

typedef struct
{
    ssize_t id1, id2;
} edge_t;
typedef edge_t* pEdge3D_t;

typedef struct
{
    pEdge3D_t edges;
    ssize_t count;
} edgeArray_t;

typedef struct
{
    pointArray_t points;
    edgeArray_t edges;
} wireframe_t;

wireframe_t initWireframe(void);
err_code_e freeWireframe(wireframe_t &wireframe);
err_code_e moveWireframe(wireframe_t &dst, const wireframe_t &src);
err_code_e freePoints(pointArray_t &points);
err_code_e freeEdges(edgeArray_t &edges);
err_code_e checkWireframe(const wireframe_t &wireframe);

#endif /* WIREFRAME_H */
