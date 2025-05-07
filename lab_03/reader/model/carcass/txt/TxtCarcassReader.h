#pragma once

#include "../CarcassReader.h"

class TxtCarcassReader : public CarcassReader
{
public:
    TxtCarcassReader() = delete;
    TxtCarcassReader(const std::string &filename);

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;

    ~TxtCarcassReader() override;
};