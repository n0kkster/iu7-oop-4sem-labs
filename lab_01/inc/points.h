#ifndef POINTS_H
#define POINTS_H

#include <cstdlib>
#include <cstdio>
#include "errors.h"

typedef struct
{
    double x, y, z;
} point_t;
typedef point_t* pPoints_t;

typedef struct
{
    pPoints_t points;
    ssize_t count;
} pointArray_t;

err_code_e readPoints(/* OUT */ pointArray_t &points, FILE *file);
err_code_e writePoints(FILE *file, const pointArray_t &points);
err_code_e deepCopyPoints(/* OUT */ pointArray_t &dst, const pointArray_t &src);

#endif /* POINTS_H */
