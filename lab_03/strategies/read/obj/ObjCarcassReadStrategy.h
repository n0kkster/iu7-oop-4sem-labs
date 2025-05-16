// ObjCarcassReadStrategy.h
#pragma once

#include "../BaseCarcassReadStrategy.h"

class ObjCarcassReadStrategy : public BaseCarcassReadStrategy
{
public:
    ObjCarcassReadStrategy() = delete;
    ObjCarcassReadStrategy(std::shared_ptr<std::ifstream> file);
    virtual ~ObjCarcassReadStrategy() override = default;
    
    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};