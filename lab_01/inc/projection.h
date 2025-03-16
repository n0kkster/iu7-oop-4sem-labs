#ifndef PROJECTION_H
#define PROJECTION_H

#include "wireframe.h"

typedef struct
{
    double x, y;
} point2D_t;

typedef struct
{
    point2D_t start, end;
} edge2D_t;

err_code_e projectEdge(/* VAR */ edge2D_t &edge2D, const edge_t &edge3D, const pointArray_t &points);

#endif /* PROJECTION_H */
