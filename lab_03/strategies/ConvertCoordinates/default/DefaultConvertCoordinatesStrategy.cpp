#include "DefaultConvertCoordinatesStrategy.h"

void DefaultConvertCoordinateStrategy::convertPoint(std::vector<Vertex> &vertices, const size_t width,
                                                    const size_t height)
{
    size_t centerX = static_cast<size_t>(width / 2.0);
    size_t centerY = static_cast<size_t>(height / 2.0);

    for (auto &point : vertices)
    {
        point.setX(point.getX() * centerX + centerX);
        point.setY(-point.getY() * centerY + centerY);
    }
}
