#ifndef HANDLER_H
#define HANDLER_H

#include "wireframe.h"
#include "errors.h"

#include "io.h"
#include "draw.h"
#include "morph.h"

typedef enum
{
    LOAD,
    SAVE,
    SHIFT,
    SCALE,
    ROTATE,
    DRAW
} action_e;

typedef struct
{
    action_e action;
    union
    {
        io_params_t io_params;
        draw_params_t draw_params;
        morph_params_t morph_params;
        // nullptr_t null_params;
    };
} action_params_t;

err_code_e handleAction(const action_params_t &action);

#endif /* HANDLER_H */
