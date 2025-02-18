#include "io.h"

err_code_e handleReadFromFile(const io_params_t &params, /* VAR */ wireframe_t &wireframe)
{
    err_code_e rc;
    wireframe_t temp;

    qDebug() << "reading from file:" << params.filename;

    rc = readDataFromFile(params.filename, temp);

    wireframe = temp;
    
    return rc;
}

err_code_e readDataFromFile(const char *filename, /* OUT */ wireframe_t &wireframe)
{
    err_code_e rc = ERROR_SUCCESS;
    FILE *file;

    file = fopen(filename, "r");    
    rc = readNumFromFile(file, wireframe.points_count);
    if (rc == ERROR_SUCCESS)
    {
        qDebug() << "points count:" << wireframe.points_count;
        rc = readPointsFromFile(file, wireframe.points_count, wireframe.points);
        if (rc == ERROR_SUCCESS)
        {
            rc = readNumFromFile(file, wireframe.edges_count);
            if (rc == ERROR_SUCCESS)
                rc = readEdgesFromFile(file, wireframe.edges_count, wireframe.edges);
        }
    }

    fclose(file);

    return rc;
}

err_code_e readEdgesFromFile(FILE *file, size_t count, /* OUT */ edgeArray_t &edges)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    edges = (edgeArray_t)malloc(count * sizeof(edge_t));
    if (edges == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            rc = readEdgeFromFile(file, edges[i]);
            if (rc != ERROR_SUCCESS)
                break;
        }
    }        

    return rc;
}

err_code_e readEdgeFromFile(FILE *file, /* OUT */ edge_t &t)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%zu%zu", &t.id1, &t.id2) != 2)
        rc = ERROR_NOT_A_NUMBER;
    else
        qDebug() << "read edge:" << t.id1 << t.id2;

    return rc;
}

err_code_e readPointsFromFile(FILE *file, size_t count, /* OUT */ pointArray_t &points)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    points = (pointArray_t)malloc(count * sizeof(point_t));
    if (points == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            rc = readPointFromFile(file, points[i].coord);
            if (rc != ERROR_SUCCESS)
                break;
            points[i].id = i;
        }
    }        

    return rc;
}

err_code_e readPointFromFile(FILE *file, /* OUT */ pointCoord_t &p)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%lf%lf%lf", &p.x, &p.y, &p.z) != 3)
        rc = ERROR_NOT_A_NUMBER;
    else
        qDebug() << "read point:" << p.x << p.y << p.z;
    

    return rc;
}

err_code_e readNumFromFile(FILE *file, /* OUT */ size_t &num)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%zu", &num) != 1)
        rc = ERROR_NOT_A_NUMBER;
    
    return rc;
}
