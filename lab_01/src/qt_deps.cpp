#include "qt_deps.h"

void realCoordsToScreenCoords(/* VAR */ point2D_t &point, const plane_size_t &plane_size)
{
    point.x = point.x + plane_size.width / 2.0;
    point.y = -point.y + plane_size.height / 2.0;
}

err_code_e drawLine(/* VAR */ painter_t &painter, const point2D_t &start, const point2D_t &end)
{
    if (painter.painter == nullptr)
        return ERROR_INVALID_PTR;

    painter.painter->drawLine(start.x, start.y, end.x, end.y);
    return ERROR_SUCCESS;
}