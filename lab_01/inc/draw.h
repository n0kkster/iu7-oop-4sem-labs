#ifndef DRAW_H
#define DRAW_H

#include <QPointF>
#include "wireframe.h"
#include "plane.h"

typedef struct
{
    double x, y;
} point2D_t;

typedef struct
{
    point2D_t start, end;
} edge2D_t;
typedef edge2D_t* pEdge2D_t;

typedef struct
{
    pEdge2D_t edges;
    ssize_t count;
} edge2DArray_t;

typedef struct 
{
    Plane *plane;
} draw_params_t;

void handleDraw(const draw_params_t &params, const wireframe_t &wireframe);

#endif /* DRAW_H */
