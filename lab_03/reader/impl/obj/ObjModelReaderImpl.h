#pragma once

#include "../BaseModelReaderImpl.h"

class ObjModelReaderImpl : public BaseModelReaderImpl
{
public:
    ObjModelReaderImpl() = delete;
    ObjModelReaderImpl(const std::string &filename);
    virtual ~ObjModelReaderImpl() override = default;
    
    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};