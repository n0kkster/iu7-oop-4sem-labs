#ifndef IO_H
#define IO_H

#include <QDebug>

#include <cstdio>
#include "wireframe.h"
#include "errors.h"

typedef char* pchar_t;

typedef struct
{
    const char *filename;
} io_params_t;

err_code_e handleReadFromFile(const io_params_t &params, wireframe_t &wireframe);

err_code_e readDataFromFile(const char *filename, wireframe_t &wireframe);
// err_code_e saveDataToFile(const io_params_t &params, wireframe_t &wireframe);

err_code_e readPointFromFile(FILE *file, pointCoord_t &p);
err_code_e readPointsFromFile(FILE *file, size_t count, pointArray_t &points);
err_code_e readEdgeFromFile(FILE *file, edge_t &t);
err_code_e readEdgesFromFile(FILE *file, size_t count, edgeArray_t &edges);
err_code_e readNumFromFile(FILE *file, size_t &num);

#endif /* IO_H */
