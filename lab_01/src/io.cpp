#include "io.h"

static err_code_e readEdgeFromFile(/* OUT */ edge_t &t, FILE *file)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%zu%zu", &t.id1, &t.id2) != 2)
        rc = ERROR_NOT_A_NUMBER;

    return rc;
}

static err_code_e readEdgesFromFile(/* OUT */ pEdgeArray_t &edges, FILE *file, const long count)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    if (count <= 0)
        return ERROR_INVALID_EDGES_COUNT;

    err_code_e rc = ERROR_SUCCESS;

    edges = (pEdgeArray_t)malloc(count * sizeof(edge_t));
    if (edges == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
    {
        for (long i = 0; i < count && rc == ERROR_SUCCESS; i++)
            rc = readEdgeFromFile(edges[i], file);
    }

    return rc;
}

static err_code_e readPointFromFile(/* OUT */ point_t &p, FILE *file)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%lf%lf%lf", &p.x, &p.y, &p.z) != 3)
        rc = ERROR_NOT_A_NUMBER;    

    return rc;
}

static err_code_e readPointsFromFile(/* OUT */ pPointArray_t &points, FILE *file, const long count)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    if (count <= 0)
        return ERROR_INVALID_POINTS_COUNT;

    err_code_e rc = ERROR_SUCCESS;

    points = (pPointArray_t)malloc(count * sizeof(point_t));
    if (points == nullptr)
        rc = ERROR_ALLOCATING_MEM;
    else
    {
        for (long i = 0; i < count && rc == ERROR_SUCCESS; i++)
            rc = readPointFromFile(points[i], file);
    }        

    return rc;
}

static err_code_e readNumFromFile(/* OUT */ long &num, FILE *file)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%ld", &num) != 1)
        rc = ERROR_NOT_A_NUMBER;
    
    return rc;
}

static err_code_e readDataFromFile(/* OUT */ wireframe_t &wireframe, const char *filename)
{
    FILE *file = fopen(filename, "r");
    err_code_e rc = readNumFromFile(wireframe.points_count, file);
    if (rc != ERROR_SUCCESS) {}
    else
    {
        rc = readPointsFromFile(wireframe.points, file, wireframe.points_count);
        if (rc != ERROR_SUCCESS) {}
        else
        {
            rc = readNumFromFile(wireframe.edges_count, file);
            if (rc == ERROR_SUCCESS) 
                rc = readEdgesFromFile(wireframe.edges, file, wireframe.edges_count);
        }
    }

    fclose(file);

    return rc;
}

err_code_e handleReadFromFile(/* VAR */ wireframe_t &wireframe, const io_params_t &params)
{
    wireframe_t temp;

    err_code_e rc = readDataFromFile(temp, params.filename);
    if (rc != ERROR_SUCCESS) {}
    else
    {
        freeWireframe(wireframe);
        copyWireframe(wireframe, temp);
    }
    
    return rc;
}

static err_code_e writePointToFile(FILE *file, const point_t &point)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;
    
    fprintf(file, "%lf%lf%lf\n", point.x, point.y, point.z);
    return ERROR_SUCCESS;
}

static err_code_e writePointsToFile(FILE *file, const size_t count, const pPointArray_t &points)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    if (points == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    fprintf(file, "%zu\n", count);
    for (size_t i = 0; i < count && rc == ERROR_SUCCESS; i++)
        rc = writePointToFile(file, points[i]);

    return rc;
}

static err_code_e writeEdgeToFile(FILE *file, const edge_t &edge)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;
    
    fprintf(file, "%zu %zu\n", edge.id1, edge.id2);
    return ERROR_SUCCESS;
}

static err_code_e writeEdgesToFile(FILE *file, const size_t count, const pEdgeArray_t &edges)
{
    if (file == nullptr)
        return ERROR_OPENING_FILE;

    if (edges == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    fprintf(file, "%zu\n", count);
    for (size_t i = 0; i < count && rc == ERROR_SUCCESS; i++)
        rc = writeEdgeToFile(file, edges[i]);

    return rc;
}

err_code_e handleWriteToFile(const io_params_t &params, const wireframe_t &wireframe)
{
    FILE *file = fopen(params.filename, "w");

    err_code_e rc = writePointsToFile(file, wireframe.points_count, wireframe.points);
    if (rc == ERROR_SUCCESS)
        rc = writeEdgesToFile(file, wireframe.edges_count, wireframe.edges);
    
    fclose(file);
    
    return rc;
}
