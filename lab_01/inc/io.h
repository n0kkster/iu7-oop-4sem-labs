#ifndef IO_H
#define IO_H

#include <cstdio>
#include "wireframe.h"
#include "errors.h"
#include "projection.h"

typedef struct
{
    const char *filename;
} io_params_t;

err_code_e handleRead(/* VAR */ wireframe_t &wireframe, const io_params_t &params);
err_code_e handleWrite(const io_params_t &params, const wireframe_t &wireframe);

#endif /* IO_H */
