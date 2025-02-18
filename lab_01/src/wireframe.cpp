#include "wireframe.h"
#include <QDebug>
wireframe_t initWireframe()
{
    wireframe_t wireframe;
    
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    wireframe.center = {0, 0, 0};
    wireframe.edges = nullptr;
    wireframe.points = nullptr;

    qDebug() << "called init";

    return wireframe;
}