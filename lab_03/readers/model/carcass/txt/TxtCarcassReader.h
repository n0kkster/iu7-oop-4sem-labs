#pragma once

#include "../CarcassReader.h"

class TxtCarcassReader : public CarcassReader
{
public:
    TxtCarcassReader() = delete;
    TxtCarcassReader(const std::string &filename);

    virtual ~TxtCarcassReader() override;

    std::vector<Vertex> readVertices() override;
    std::vector<Edge> readEdges() override;
};