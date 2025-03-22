#ifndef HANDLER_H
#define HANDLER_H

#include <cstddef>
#include "io.h"
#include "projection.h"
#include "morph.h"
#include "draw.h"

typedef enum
{
    LOAD,
    SAVE,
    MOVE,
    SCALE,
    ROTATE,
    DRAW,
    FREE
} action_e;

typedef struct
{
    action_e action;
    union
    {
        io_params_t io_params;
        shift_params_t shift_params;
        scale_params_t scale_params;
        rotation_params_t rotation_params;
        nullptr_t null_params;
    };
} action_params_t;

err_code_e handleAction(plane_t &plane, const action_params_t &action);

#endif /* HANDLER_H */
