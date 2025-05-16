// CsvCarcassReadStrategy.h
#pragma once

#include "../BaseCarcassReadStrategy.h"

class CsvCarcassReadStrategy : public BaseCarcassReadStrategy
{
public:
    CsvCarcassReadStrategy() = delete;
    CsvCarcassReadStrategy(std::shared_ptr<std::ifstream> file);
    virtual ~CsvCarcassReadStrategy() override = default;

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
