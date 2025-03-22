#include "io.h"
#include "edges.h"
#include "points.h"

static err_code_e readData(/* OUT */ wireframe_t &wireframe, const char *filename)
{
    if (filename == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;
    FILE *file = fopen(filename, "r");

    if (file == nullptr)
        rc = ERROR_OPENING_FILE;
    else
    {
        rc = readPoints(wireframe.points, file);
        if (rc == ERROR_SUCCESS)
        {
            rc = readEdges(wireframe.edges, file);
            if (rc != ERROR_SUCCESS)
                freePoints(wireframe.points);
        }
        
        fclose(file);
    }

    return rc;
}

err_code_e handleRead(/* VAR */ wireframe_t &wireframe, const io_params_t &params)
{
    wireframe_t temp;

    err_code_e rc = readData(temp, params.filename);
    if (rc == ERROR_SUCCESS)
    {
        rc = checkWireframe(temp);
        if (rc != ERROR_SUCCESS)
            freeWireframe(temp);
        else
            moveWireframe(wireframe, temp);
    }
    
    return rc;
}

err_code_e handleWrite(const io_params_t &params, const wireframe_t &wireframe)
{
    FILE *file = fopen(params.filename, "w");
    err_code_e rc = ERROR_SUCCESS;

    if (file == nullptr)
        rc = ERROR_OPENING_FILE;
    else
    {
        rc = writePoints(file, wireframe.points);
        if (rc == ERROR_SUCCESS)
            rc = writeEdges(file, wireframe.edges);
    }
    
    fclose(file);
    
    return rc;
}
