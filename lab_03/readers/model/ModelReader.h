#pragma once

#include "../../component/primitive/visible/model/edge/edge.h"
#include "../../component/primitive/visible/model/vertex/vertex.h"
#include "../BaseReader.h"

#include <memory>
#include <vector>

class ModelReader : public BaseReader
{
protected:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;

public:
    ModelReader() = delete;
    ModelReader(const std::string &filename) : BaseReader(filename) { };

    virtual ~ModelReader() = default;

    virtual std::shared_ptr<std::vector<Vertex>> readVertices() = 0;
    virtual std::shared_ptr<std::vector<Edge>> readEdges() = 0;
};
