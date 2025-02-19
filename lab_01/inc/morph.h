#ifndef MORPH_H
#define MORPH_H

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
} transform_params_t;

typedef struct
{
    double cx, cy, cz;
    double angle;
} rotation_params_t;

typedef struct
{
    union
    {
        shift_params_t shift_params;
        transform_params_t transform_params;
        rotation_params_t rotation_params;
    };
    
} morph_params_t;

#endif /* MORPH_H */
