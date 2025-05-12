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

    virtual std::vector<Vertex> readVertices() = 0;
    virtual std::vector<Edge> readEdges() = 0;

public:
    ModelReader() = delete;
    explicit ModelReader(const std::string &filename) : BaseReader(filename) { };

    virtual ~ModelReader() override = default;

    virtual void read(BaseBuilder &builder, size_t part) override;
};
