#include "morph.h"

static void applyPointShift(/* VAR */ point_t &point, const shift_params_t &params)
{
    point.x += params.dx;
    point.y += params.dy;
    point.z += params.dz;
}

static err_code_e applyPointsShift(/* VAR */ pointArray_t &points, const shift_params_t &params)
{
    if (points.points == nullptr)
        return ERROR_INVALID_PTR;
    
    if (points.count < 0)
        return ERROR_INVALID_POINTS_COUNT;

    for (ssize_t i = 0; i < points.count; i++)
        applyPointShift(points.points[i], params);
    
    return ERROR_SUCCESS;
}

err_code_e handleShiftWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    err_code_e rc = applyPointsShift(wireframe.points, params.shift_params);
    return rc;
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

static err_code_e applyPointsScale(/* VAR */ pointArray_t &points, const scale_params_t &params)
{
    if (points.points == nullptr)
        return ERROR_INVALID_PTR;

    if (points.count < 0)
        return ERROR_INVALID_POINTS_COUNT;

    for (ssize_t i = 0; i < points.count; i++)
        applyPointScale(points.points[i], params.origin, params.scale);
    
    return ERROR_SUCCESS;
}

err_code_e handleScaleWireframe(/* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    err_code_e rc = applyPointsScale(wireframe.points, params.scale_params);
    return rc;
}


static err_code_e rotatePointByX(/* VAR */ point_t &point, const trig_t &trigX)
{
    double ty = point.y, tz = point.z;

    point.y = ty * trigX.cos - tz * trigX.sin;
    point.z = ty * trigX.sin + tz * trigX.cos; 

    return ERROR_SUCCESS;
}

static err_code_e rotatePointByY(/* VAR */ point_t &point, const trig_t &trigY)
{
    double tx = point.x, tz = point.z;

    point.x = tx * trigY.cos + tz * trigY.sin;
    point.z = -tx * trigY.sin + tz * trigY.cos;

    return ERROR_SUCCESS;
}

static err_code_e rotatePointByZ(/* VAR */ point_t &point, const trig_t &trigZ)
{
    double tx = point.x, ty = point.y;

    point.x = tx * trigZ.cos - ty * trigZ.sin;
    point.y = tx * trigZ.sin + ty * trigZ.cos;

    return ERROR_SUCCESS;
}

static void rotatePoint(/* VAR */ point_t &point, const trig_set_t &trigSet)
{
    rotatePointByX(point, trigSet.trigX);
    rotatePointByY(point, trigSet.trigY);
    rotatePointByZ(point, trigSet.trigZ);
}

static void applyPointRotation(/* VAR */ point_t &point, const origin_t &origin, const trig_set_t &trigSet)
{
    applyPointShift(point, {-origin.cx, -origin.cy, -origin.cz});
    rotatePoint(point, trigSet);
    applyPointShift(point, {origin.cx, origin.cy, origin.cz});
}

static void calculateTrigAngle(/* OUT */ trig_t &trig, const double angle)
{
    trig.sin = sin(angle);
    trig.cos = cos(angle);
}

static void calculateTrigAngles(/* OUT */ trig_set_t &trigSet, const angle_t &angle)
{
    calculateTrigAngle(trigSet.trigX, angle.angleX);
    calculateTrigAngle(trigSet.trigY, angle.angleY);
    calculateTrigAngle(trigSet.trigZ, angle.angleZ);
}

static err_code_e applyWireframeRotation(/* VAR */ pointArray_t &points, const rotation_params_t &params)
{
    if (points.points == nullptr)
        return ERROR_INVALID_PTR;

    if (points.count < 0)
        return ERROR_INVALID_POINTS_COUNT;

    trig_set_t trigSet;

    calculateTrigAngles(trigSet, params.angle);

    for (ssize_t i = 0; i < points.count; i++)
        applyPointRotation(points.points[i], params.origin, trigSet);

    return ERROR_SUCCESS;
}

err_code_e handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params)
{
    err_code_e rc = applyWireframeRotation(wireframe.points, params.rotation_params);
    return rc;
}