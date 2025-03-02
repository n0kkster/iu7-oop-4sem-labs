#include "morph.h"

static void applyPointShift(/* VAR */ point_t &point, const shift_params_t &params)
{
    point.x += params.dx;
    point.y += params.dy;
    point.z += params.dz;
}

static void applyWireframeShift(/* VAR */ pointArray_t &points, const shift_params_t &params)
{
    for (ssize_t i = 0; i < points.count; i++)
        applyPointShift(points.points[i], params);
}

void handleShiftWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeShift(wireframe.points, params.shift_params);
}

static void scalePoint(/* VAR */ point_t &point, const scale_t &scale)
{
    point.x *= scale.kx;
    point.y *= scale.ky;
    point.z *= scale.kz;
}

static void applyPointScale(/* VAR */ point_t &point, const origin_t &origin, const scale_t &scale)
{
    applyPointShift(point, {-origin.cx, -origin.cy, -origin.cz});
    scalePoint(point, scale);
    applyPointShift(point, {origin.cx, origin.cy, origin.cz});
}

static void applyWireframeScale(/* VAR */ pointArray_t &points, const scale_params_t &params)
{
    for (ssize_t i = 0; i < points.count; i++)
        applyPointScale(points.points[i], params.origin, params.scale);
}

void handleScaleWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeScale(wireframe.points, params.scale_params);
}

// TODO: разибить на 3 функции
static void rotatePoint(/* VAR */ point_t &point, const angle_t &angle)
{
    double tx = point.x, ty = point.y, tz = point.z;
    double angleX = angle.angleX, angleY = angle.angleY, angleZ = angle.angleZ;

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
}

static void applyPointRotation(/* VAR */ point_t &point, const origin_t &origin, const angle_t &angle)
{
    applyPointShift(point, {-origin.cx, -origin.cy, -origin.cz});
    rotatePoint(point, angle);
    applyPointShift(point, {origin.cx, origin.cy, origin.cz});
}

static void applyWireframeRotation(/* VAR */ pointArray_t &points, const rotation_params_t &params)
{
    for (ssize_t i = 0; i < points.count; i++)
        applyPointRotation(points.points[i], params.origin, params.angle);
}

void handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    applyWireframeRotation(wireframe.points, params.rotation_params);
}