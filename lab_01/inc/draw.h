#ifndef DRAW_H
#define DRAW_H

#include "errors.h"
#include "wireframe.h"
#include "projection.h"
#include "qt_deps.h"

typedef struct
{
    painter_t painter;
    plane_size_t plane_size;
} plane_t;

err_code_e handleDraw(/* VAR */ plane_t &plane, const wireframe_t &wireframe);

#endif /* DRAW_H */
