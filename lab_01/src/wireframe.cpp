#include "wireframe.h"
#include <QDebug>

wireframe_t initWireframe()
{
    wireframe_t wireframe;
    
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    wireframe.edges = nullptr;
    wireframe.points = nullptr;

    return wireframe;
}

void freeWireframe(wireframe_t &wireframe)
{
    wireframe.edges_count = 0;
    wireframe.points_count = 0;
    free(wireframe.edges);
    free(wireframe.points);
}