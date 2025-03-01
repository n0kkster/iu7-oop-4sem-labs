#include "edges.h"

static err_code_e readAmountOfEdges(/* OUT */ long &edgesCount, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%ld", &edgesCount) != 1)
        rc = ERROR_NOT_A_NUMBER;

    if (edgesCount <= 0)
        rc = ERROR_INVALID_EDGES_COUNT;
    
    return rc;
}

static err_code_e readEdge(/* OUT */ edge_t &t, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    if (fscanf(file, "%zu%zu", &t.id1, &t.id2) != 2)
        rc = ERROR_NOT_A_NUMBER;

    return rc;
}

static err_code_e readEdgesArray(/* OUT */ pEdges_t edges, FILE *file, const long edgesCount)
{
    if (file == nullptr || edges == nullptr)
        return ERROR_INVALID_PTR;
    
    if (edgesCount <= 0)
        return ERROR_INVALID_EDGES_COUNT;

    err_code_e rc = ERROR_SUCCESS;
    for (long i = 0; rc == ERROR_SUCCESS && i < edgesCount; i++)
        rc = readEdge(edges[i], file);

    return rc;
}

err_code_e readEdges(/* OUT */ edgeArray_t &edges, FILE *file)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = readAmountOfEdges(edges.count, file);

    if (rc == ERROR_SUCCESS)
    {
        edges.edges = (pEdges_t)malloc(edges.count * sizeof(edge_t));
        if (edges.edges == nullptr)
            rc = ERROR_ALLOCATING_MEM;
        else
        {
            rc = readEdgesArray(edges.edges, file, edges.count);
            if (rc != ERROR_SUCCESS)
            {
                free(edges.edges);
                edges.count = 0;
            }
        }
    }
    return rc;
}

static err_code_e writeEdge(FILE *file, const edge_t &edge)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;
    
    fprintf(file, "%zu %zu\n", edge.id1, edge.id2);
    return ERROR_SUCCESS;
}

err_code_e writeEdges(FILE *file, const edgeArray_t &edges)
{
    if (file == nullptr)
        return ERROR_INVALID_PTR;

    if (edges.edges == nullptr)
        return ERROR_INVALID_PTR;

    err_code_e rc = ERROR_SUCCESS;

    fprintf(file, "%zu\n", edges.count);
    for (size_t i = 0; rc == ERROR_SUCCESS && i < edges.count; i++)
        rc = writeEdge(file, edges.edges[i]);

    return rc;
}
