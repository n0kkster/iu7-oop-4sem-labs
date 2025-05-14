#pragma once

#include "../BaseCarcassReadStrategy.h"

class TxtCarcassReadStrategy : public BaseCarcassReadStrategy
{
public:
    TxtCarcassReadStrategy() = delete;
    TxtCarcassReadStrategy(std::shared_ptr<std::ifstream> file);
    virtual ~TxtCarcassReadStrategy() override = default;
    
    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};