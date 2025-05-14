#pragma once

#include "../../component/primitive/visible/model/edge/Edge.h"
#include "../../component/primitive/visible/model/vertex/Vertex.h"

#include <vector>
#include <fstream>
#include <memory>

class BaseCarcassReadStrategy
{
protected:
    std::shared_ptr<std::ifstream> m_file;    

public:
    BaseCarcassReadStrategy() = delete;
    BaseCarcassReadStrategy(std::shared_ptr<std::ifstream> file);
    virtual ~BaseCarcassReadStrategy() = default;

    virtual std::shared_ptr<std::vector<Vertex>> readVertices() = 0;
    virtual std::shared_ptr<std::vector<Edge>> readEdges() = 0;
};
