#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <cstdio>
#include <cstdlib>
#include "errors.h"

typedef struct
{
    double x, y, z;
} point_t;

typedef point_t* pPointArray_t;

typedef struct
{
    size_t id1, id2;
} edge_t;
typedef edge_t* pEdgeArray_t;

typedef struct
{
    pPointArray_t points;
    pEdgeArray_t edges;
    long points_count;
    long edges_count;
} wireframe_t;

wireframe_t initWireframe(void);
void freeWireframe(wireframe_t &wireframe);
void copyWireframe(wireframe_t &dst, const wireframe_t &src);
err_code_e checkWireframe(const wireframe_t &wireframe);

#endif /* WIREFRAME_H */
