#ifndef MORPH_H
#define MORPH_H

#include <QDebug>
#include <math.h>
#include "wireframe.h"

typedef struct
{
    double dx, dy, dz;
} shift_params_t;

typedef struct
{
    double cx, cy, cz;
    double kx, ky, kz;
} scale_params_t;

typedef struct
{
    double cx, cy, cz;
    double angleX, angleY, angleZ;
} rotation_params_t;

typedef struct
{
    union
    {
        shift_params_t shift_params;
        scale_params_t scale_params;
        rotation_params_t rotation_params;
    };
    
} morph_params_t;

void handleShiftWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe);
void applyWireframeShift(const shift_params_t &params, size_t count, /* VAR */ pointArray_t &points);
void applyPointShift(const shift_params_t &params, /* VAR */ pointCoord_t &point);
void handleScaleWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe);
void applyWireframeScale(const scale_params_t &params, size_t count, /* VAR */ pointArray_t &points);
void applyPointScale(const scale_params_t &params, /* VAR */ pointCoord_t &point);
void handleRotateWireframe(const morph_params_t &params, /* VAR */ wireframe_t &wireframe);
void applyWireframeRotation(const rotation_params_t &params, size_t count, /* VAR */ pointArray_t &points);
void applyPointRotation(const rotation_params_t &params, /* VAR */ pointCoord_t &point);
double degToRad(double degrees);

#endif /* MORPH_H */
