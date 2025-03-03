#ifndef PROJECTION_H
#define PROJECTION_H

#include <QPointF>
#include "wireframe.h"

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
    edge2DArray_t edges;
} projection_t;

err_code_e initProjection(/* OUT */ projection_t &projection);
err_code_e freeProjection(/* VAR */ projection_t &projection);
err_code_e createProjection(/* OUT */ projection_t &projection, const wireframe_t &wireframe);
err_code_e updateProjection(/* VAR */ projection_t &projection, const wireframe_t &wireframe);

#endif /* PROJECTION_H */
