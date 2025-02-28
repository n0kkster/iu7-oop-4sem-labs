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

void handleShiftWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);
void handleScaleWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);
void handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);

#endif /* MORPH_H */
