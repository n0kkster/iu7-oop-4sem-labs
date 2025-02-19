#ifndef DRAW_H
#define DRAW_H

#include <QPointF>
#include "wireframe.h"
#include "plane.h"

typedef struct 
{
    Plane *plane;
} draw_params_t;

void handleDraw(const draw_params_t &params, wireframe_t &wireframe);
void addPointsToCanvas(Plane *plane, size_t count, pointArray_t points);
void addEdgesToCanvas(Plane *plane, size_t count, edgeArray_t edges);
QPointF projectPoint(pointCoord_t &point);

#endif /* DRAW_H */
