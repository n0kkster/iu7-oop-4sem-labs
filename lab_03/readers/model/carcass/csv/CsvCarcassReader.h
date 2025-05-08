#pragma once

#include "../CarcassReader.h"

class CsvCarcassReader : public CarcassReader
{
public:
    CsvCarcassReader() = delete;
    CsvCarcassReader(const std::string &filename);

    std::vector<Vertex> readVertices() override;
    std::vector<Edge> readEdges() override;

    virtual ~CsvCarcassReader() override;
};