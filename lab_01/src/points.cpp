#include "points.h"

static err_code_e readAmountOfPoints(/* OUT */ ssize_t &pointsCount, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%ld", &pointsCount) != 1)
        rc = ERROR_NOT_A_NUMBER;
    else
    {
        if (pointsCount <= 0)
            rc = ERROR_INVALID_POINTS_COUNT;
    }
    
    return rc;
}

static err_code_e readPoint(/* OUT */ point_t &p, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%lf%lf%lf", &p.x, &p.y, &p.z) != 3)
        rc = ERROR_NOT_A_NUMBER;    

    return rc;
}

static err_code_e readPointsArray(/* OUT */ pPoints_t points, FILE *file, const ssize_t pointsCount)
{
    if (points == nullptr)
        return ERROR_INVALID_PTR;
    
    if (pointsCount <= 0)
        return ERROR_INVALID_POINTS_COUNT;

    err_code_e rc = ERROR_SUCCESS;
    for (ssize_t i = 0; rc == ERROR_SUCCESS && i < pointsCount; i++)
        rc = readPoint(points[i], file);

    return rc;
}

err_code_e readPoints(/* OUT */ pointArray_t &points, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = readAmountOfPoints(points.count, file);

    if (rc == ERROR_SUCCESS)
    {
        points.points = (pPoints_t)malloc(points.count * sizeof(point_t));
        if (points.points == nullptr)
            rc = ERROR_ALLOCATING_MEM;
        else
        {
            rc = readPointsArray(points.points, file, points.count);
            if (rc != ERROR_SUCCESS)
                free(points.points);
        }  
    }      

    return rc;
}

static err_code_e writePoint(FILE *file, const point_t &point)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;
    
    fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z);
    return ERROR_SUCCESS;
}

err_code_e writePoints(FILE *file, const pointArray_t &points)
{
    if (file == nullptr || points.points)
        return ERROR_INVALID_PTR;

    if (points.count <= 0)
        return ERROR_INVALID_POINTS_COUNT;

    err_code_e rc = ERROR_SUCCESS;

    fprintf(file, "%zu\n", points.count);
    for (ssize_t i = 0; rc == ERROR_SUCCESS && i < points.count; i++)
        rc = writePoint(file, points.points[i]);

    return rc;
}

static void copyPoint(/* OUT */ point_t &dst, const point_t &src)
{
    dst = src;
}

static err_code_e copyPointsArray(/* OUT */ pPoints_t dst, const pPoints_t src, const ssize_t length)
{
    if (dst == nullptr || src == nullptr)
        return ERROR_INVALID_PTR;

    if (length <= 0)
        return ERROR_INVALID_EDGES_COUNT;

    for (ssize_t i = 0; i < length; i++)
        copyPoint(dst[i], src[i]);

    return ERROR_SUCCESS;
}

err_code_e deepCopyPoints(/* OUT */ pointArray_t &dst, const pointArray_t &src)
{
    if (src.count <= 0)
        return ERROR_INVALID_EDGES_COUNT;

    err_code_e rc = ERROR_SUCCESS;

    dst.points = (pPoints_t)malloc(src.count * sizeof(point_t));
    if (dst.points == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
    {
        rc = copyPointsArray(dst.points, src.points, src.count);
        if (rc != ERROR_SUCCESS)
            free(dst.points);
        else
            dst.count = src.count;
    }
    return rc;
}
