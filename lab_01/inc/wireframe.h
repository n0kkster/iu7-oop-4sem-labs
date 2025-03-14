#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <cstdio>
#include "errors.h"

#include "points.h"
#include "edges.h"

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
err_code_e checkWireframe(const wireframe_t &wireframe);
err_code_e deepCopyWireframe(/* OUT */ wireframe_t &dst, const wireframe_t &src);

#endif /* WIREFRAME_H */
