#include "morph.h"

void handleShiftWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe)
{
    applyWireframeShift(params.shift_params, wireframe.points_count, wireframe.points);
}

void applyWireframeShift(const shift_params_t &params, size_t count, /* VAR */ pointArray_t &points)
{
    for (size_t i = 0; i < count; i++)
        applyPointShift(params, points[i].coord);
}

void applyPointShift(const shift_params_t &params, /* VAR */ pointCoord_t &point)
{
    point.x += params.dx;
    point.y += params.dy;
    point.z += params.dz;
}

void handleScaleWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe)
{
    applyWireframeScale(params.scale_params, wireframe.points_count, wireframe.points);
}

void applyWireframeScale(const scale_params_t &params, size_t count, /* VAR */ pointArray_t &points)
{
    for (size_t i = 0; i < count; i++)
        applyPointScale(params, points[i].coord);
}

void applyPointScale(const scale_params_t &params, /* VAR */ pointCoord_t &point)
{
    point.x = (point.x - params.cx) * params.kx + params.cx;
    point.y = (point.y - params.cy) * params.ky + params.cy;
    point.z = (point.z - params.cz) * params.kz + params.cz;
}

void handleRotateWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe)
{
    applyWireframeRotation(params.rotation_params, wireframe.points_count, wireframe.points);
}

void applyWireframeRotation(const rotation_params_t &params, size_t count, /* VAR */ pointArray_t &points)
{
    for (size_t i = 0; i < count; i++)
        applyPointRotation(params, points[i].coord);
}

void applyPointRotation(const rotation_params_t &params, /* VAR */ pointCoord_t &point)
{
    double angleX = degToRad(params.angleX);
    double angleY = degToRad(params.angleY);
    double angleZ = degToRad(params.angleZ);

    point.x -= params.cx;
    point.y -= params.cy;
    point.z -= params.cz;

    double tx = point.x, ty = point.y, tz = point.z;

    point.y = ty * cos(angleX) - tz * sin(angleX);
    point.z = ty * sin(angleX) + tz * cos(angleX);

    ty = point.y;
    tz = point.z;

    point.x = tx * cos(angleY) + tz * sin(angleY);
    point.z = -tx * sin(angleY) + tz * cos(angleY);

    tx = point.x;
    tz = point.z;

    point.x = tx * cos(angleZ) - ty * sin(angleZ);
    point.y = tx * sin(angleZ) + ty * cos(angleZ);

    point.x += params.cx;
    point.y += params.cy;
    point.z += params.cz;
}

double degToRad(double degrees)
{
    return degrees * M_PI / 180;
}