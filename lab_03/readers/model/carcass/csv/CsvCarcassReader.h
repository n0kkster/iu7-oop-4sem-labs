#pragma once

#include "../CarcassReader.h"

class CsvCarcassReader : public CarcassReader
{
public:
    CsvCarcassReader() = delete;
    CsvCarcassReader(const std::string &filename);

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;

    ~CsvCarcassReader() override;
};