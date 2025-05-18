#pragma once

#include "../BaseModelReaderImpl.h"

class TxtModelReaderImpl: public BaseModelReaderImpl
{
public:
    TxtModelReaderImpl() = delete;
    TxtModelReaderImpl(const std::string &filename);
    virtual ~TxtModelReaderImpl() override = default;
    
    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};