#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <cstdio>
#include <cstdlib>

typedef struct
{
    double x, y, z;
} pointCoord_t;

typedef struct
{
    size_t id;
    pointCoord_t coord;
} point_t;
typedef point_t* pointArray_t;

typedef struct
{
    size_t id1, id2;
} edge_t;
typedef edge_t* edgeArray_t;

typedef struct
{
    pointArray_t points;
    edgeArray_t edges;
    long points_count;
    long edges_count;
} wireframe_t;

wireframe_t initWireframe(void);
void freeWireframe(wireframe_t &wireframe);
void copyWireframe(wireframe_t &dst, const wireframe_t &src);

#endif /* WIREFRAME_H */
