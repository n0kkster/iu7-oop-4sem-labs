#ifndef IO_H
#define IO_H

#include <cstdio>
#include "wireframe.h"
#include "errors.h"

typedef char* pchar_t;

typedef struct
{
    const char *filename;
} io_params_t;

err_code_e handleReadFromFile(const io_params_t &params, wireframe_t &wireframe);
err_code_e handleWriteToFile(const io_params_t &params, const wireframe_t &wireframe);

#endif /* IO_H */
