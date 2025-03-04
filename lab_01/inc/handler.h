#ifndef HANDLER_H
#define HANDLER_H

#include <cstddef>
#include "io.h"
#include "projection.h"
#include "morph.h"

typedef enum
{
    INIT,
    LOAD,
    SAVE,
    MORPH,
    FREE
} action_e;

typedef struct
{
    action_e action;
    union
    {
        io_params_t io_params;
        morph_params_t morph_params;
        nullptr_t null_params;
    };
} action_params_t;

err_code_e handleAction(/* VAR */ projection_t &projection, const action_params_t &action);

#endif /* HANDLER_H */
