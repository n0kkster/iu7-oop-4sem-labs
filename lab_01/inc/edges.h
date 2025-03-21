#ifndef EDGES_H
#define EDGES_H

#include <cstdlib>
#include <cstdio>
#include "errors.h"

typedef struct
{
    ssize_t id1, id2;
} edge_t;
typedef edge_t* pEdge3D_t;

typedef struct
{
    pEdge3D_t edges;
    ssize_t count;
} edgeArray_t;

err_code_e readEdges(/* OUT */ edgeArray_t &edges, FILE *file);
err_code_e writeEdges(FILE *file, const edgeArray_t &edges);

#endif /* EDGES_H */
