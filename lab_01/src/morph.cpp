#include "morph.h"

static void calculateShiftToCenter(/* OUT */ shift_params_t &shift, const origin_t &origin)
{
    shift.dx = -origin.cx;
    shift.dy = -origin.cy;
    shift.dz = -origin.cz;
}

static void calculateShiftToOrigin(/* OUT */ shift_params_t &shift, const origin_t &origin)
{
    shift.dx = origin.cx;
    shift.dy = origin.cy;
    shift.dz = origin.cz;
}

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

err_code_e handleShiftWireframe(/* VAR */ wireframe_t &wireframe, const shift_params_t &params)
{
    err_code_e rc = applyPointsShift(wireframe.points, params);
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
    shift_params_t shiftToCenter, shiftToOrigin;

    calculateShiftToCenter(shiftToCenter, origin);
    calculateShiftToOrigin(shiftToOrigin, origin);

    applyPointShift(point, shiftToCenter);
    scalePoint(point, scale);
    applyPointShift(point, shiftToOrigin);
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

err_code_e handleScaleWireframe(/* VAR */ wireframe_t &wireframe, const scale_params_t &params)
{
    err_code_e rc = applyPointsScale(wireframe.points, params);
    return rc;
}

static void rotatePointByX(/* VAR */ point_t &point, const trig_t &trigX)
{
    double ty = point.y, tz = point.z;

    point.y = ty * trigX.cos - tz * trigX.sin;
    point.z = ty * trigX.sin + tz * trigX.cos; 
}

static void rotatePointByY(/* VAR */ point_t &point, const trig_t &trigY)
{
    double tx = point.x, tz = point.z;

    point.x = tx * trigY.cos + tz * trigY.sin;
    point.z = -tx * trigY.sin + tz * trigY.cos;
}

static void rotatePointByZ(/* VAR */ point_t &point, const trig_t &trigZ)
{
    double tx = point.x, ty = point.y;

    point.x = tx * trigZ.cos - ty * trigZ.sin;
    point.y = tx * trigZ.sin + ty * trigZ.cos;
}

static void rotatePoint(/* VAR */ point_t &point, const trig_set_t &trigSet)
{
    rotatePointByX(point, trigSet.trigX);
    rotatePointByY(point, trigSet.trigY);
    rotatePointByZ(point, trigSet.trigZ);
}

static void applyPointRotation(/* VAR */ point_t &point, const origin_t &origin, const trig_set_t &trigSet)
{
    shift_params_t shiftToCenter, shiftToOrigin;

    calculateShiftToCenter(shiftToCenter, origin);
    calculateShiftToOrigin(shiftToOrigin, origin);

    applyPointShift(point, shiftToOrigin);
    rotatePoint(point, trigSet);
    applyPointShift(point, shiftToCenter);
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

err_code_e handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const rotation_params_t &params)
{
    err_code_e rc = applyWireframeRotation(wireframe.points, params);
    return rc;
}
