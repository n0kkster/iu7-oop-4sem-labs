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

#endif /* DRAW_H */
