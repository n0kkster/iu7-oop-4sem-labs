#include "morph.h"

static double degToRad(double degrees)
{
    return degrees * M_PI / 180;
}

static void applyPointShift(/* VAR */ point_t &point, const shift_params_t &params)
{
    point.x += params.dx;
    point.y += params.dy;
    point.z += params.dz;
}

static void applyWireframeShift(/* VAR */ pointArray_t &points, const shift_params_t &params)
{
    for (size_t i = 0; i < points.count; i++)
        applyPointShift(points.points[i], params);
}

void handleShiftWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeShift(wireframe.points, params.shift_params);
}

static void applyPointScale(/* VAR */ point_t &point, const scale_params_t &params)
{
    point.x = (point.x - params.cx) * params.kx + params.cx;
    point.y = (point.y - params.cy) * params.ky + params.cy;
    point.z = (point.z - params.cz) * params.kz + params.cz;
}


static void applyWireframeScale(/* VAR */ pointArray_t &points, const scale_params_t &params)
{
    for (size_t i = 0; i < points.count; i++)
        applyPointScale(points.points[i], params);
}

void handleScaleWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeScale(wireframe.points, params.scale_params);
}

static void applyPointRotation(/* VAR */ point_t &point, const rotation_params_t &params)
{
    double angleX = degToRad(params.angleX);
    double angleY = degToRad(params.angleY);
    double angleZ = degToRad(params.angleZ);

    applyPointShift(point, {-params.cx, -params.cy, -params.cz});

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

    applyPointShift(point, {params.cx, params.cy, params.cz});
}

static void applyWireframeRotation(/* VAR */ pointArray_t &points, const rotation_params_t &params)
{
    for (size_t i = 0; i < points.count; i++)
        applyPointRotation(points.points[i], params);
}

void handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeRotation(wireframe.points, params.rotation_params);
}