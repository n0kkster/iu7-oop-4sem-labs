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
    long count;
} pointArray_t;

typedef struct
{
    size_t id1, id2;
} edge_t;
typedef edge_t* pEdges_t;

typedef struct
{
    pEdges_t edges;
    long count;
} edgeArray_t;

typedef struct
{
    pointArray_t points;
    edgeArray_t edges;
} wireframe_t;

wireframe_t initWireframe(void);
void freeWireframe(wireframe_t &wireframe);
void moveWireframe(wireframe_t &dst, const wireframe_t &src);
void freePoints(pointArray_t &points);
void freeEdges(edgeArray_t &edges);
// err_code_e checkWireframe(const wireframe_t &wireframe);


#endif /* WIREFRAME_H */
