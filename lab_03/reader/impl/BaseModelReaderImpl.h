#pragma once

#include "../../component/primitive/visible/model/edge/Edge.h"
#include "../../component/primitive/visible/model/vertex/Vertex.h"

#include <vector>
#include <fstream>
#include <memory>

class BaseModelReaderImpl
{
protected:
    std::ifstream m_file;    

public:
    BaseModelReaderImpl() = delete;
    BaseModelReaderImpl(const std::string &filename);
    virtual ~BaseModelReaderImpl() = default;

    virtual std::shared_ptr<std::vector<Vertex>> readVertices() = 0;
    virtual std::shared_ptr<std::vector<Edge>> readEdges() = 0;
};