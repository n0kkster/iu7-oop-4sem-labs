#pragma once

#include "../component/primitive/visible/model/edge/Edge.h"
#include "../component/primitive/visible/model/vertex/Vertex.h"
#include "impl/BaseModelReaderImpl.h"

class ModelReader
{
private:
    std::shared_ptr<BaseModelReaderImpl> m_impl;
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;

public:
    ModelReader() = delete;
    ModelReader(std::shared_ptr<BaseModelReaderImpl> impl);

    ~ModelReader() = default;

    std::shared_ptr<std::vector<Vertex>> readVertices();
    std::shared_ptr<std::vector<Edge>> readEdges();
};
