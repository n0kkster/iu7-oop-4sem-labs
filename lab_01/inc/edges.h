#ifndef EDGES_H
#define EDGES_H

#include <cstdio>
#include "errors.h"
#include "wireframe.h"

err_code_e readEdges(/* OUT */ edgeArray_t &edges, FILE *file);
err_code_e writeEdges(FILE *file, const edgeArray_t &edges);

#endif /* EDGES_H */
