#ifndef MORPH_H
#define MORPH_H

#include <math.h>
#include "wireframe.h"

typedef struct
{
    double cx, cy, cz;
} origin_t;

typedef struct
{
    double kx, ky, kz;
} scale_t;

typedef struct
{
    double angleX, angleY, angleZ;
} angle_t;

typedef struct
{
    double dx, dy, dz;
} shift_params_t;

typedef struct
{
    origin_t origin;
    scale_t scale;
} scale_params_t;

typedef struct
{
    origin_t origin;
    angle_t angle;
} rotation_params_t;

typedef enum
{
    MOVE,
    SCALE,
    ROTATE
} morph_type_e;

typedef struct
{
    morph_type_e type;
    union
    {
        shift_params_t shift_params;
        scale_params_t scale_params;
        rotation_params_t rotation_params;
    };
    
} morph_params_t;

err_code_e handleShiftWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);
err_code_e handleScaleWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);
err_code_e handleRotateWireframe( /* VAR */ wireframe_t &wireframe, const morph_params_t &params);

#endif /* MORPH_H */
