#pragma once

#include "../ModelReader.h"
#include "../../../strategies/read/BaseCarcassReadStrategy.h"

class CarcassReader : public ModelReader
{
private:
    std::shared_ptr<BaseCarcassReadStrategy> m_strategy;

public:
    CarcassReader() = delete;
    CarcassReader(const std::string &filename);

    ~CarcassReader() override;

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
