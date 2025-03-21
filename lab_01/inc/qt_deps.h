#ifndef QT_DEPS_H
#define QT_DEPS_H

#include <QPainter>
#include "projection.h"
#include "errors.h"

typedef struct
{
    QPainter *painter;
} painter_t;

typedef struct
{
    size_t width, height;
} plane_size_t;

void realCoordsToScreenCoords(/* VAR */ point2D_t &point, const plane_size_t &plane_size);
err_code_e drawLine(/* VAR */ painter_t &painter, const point2D_t &start, const point2D_t &stop);

#endif /* QT_DEPS_H */
