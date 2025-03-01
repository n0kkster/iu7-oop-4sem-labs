#ifndef POINTS_H
#define POINTS_H

#include <cstdio>
#include "errors.h"
#include "wireframe.h"

err_code_e readPoints(/* OUT */ pointArray_t &points, FILE *file);
err_code_e writePoints(FILE *file, const pointArray_t &points);

#endif /* POINTS_H */
