#ifndef DRAW_H
#define DRAW_H

#include <QPointF>
#include "wireframe.h"
#include "plane.h"

typedef struct 
{
    Plane *plane;
} draw_params_t;

void handleDraw(const draw_params_t &params, const wireframe_t &wireframe);
void addPointsToCanvas(Plane *plane, size_t count, const pointArray_t points);
void addEdgesToCanvas(Plane *plane, size_t count, const edgeArray_t edges);
QPointF projectPoint(const pointCoord_t &point);

#endif /* DRAW_H */
