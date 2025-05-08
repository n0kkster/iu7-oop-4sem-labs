#pragma once

#include "../CarcassReader.h"

class ObjCarcassReader : public CarcassReader
{
public:
    ObjCarcassReader() = delete;
    ObjCarcassReader(const std::string &filename);

    std::vector<Vertex> readVertices() override;
    std::vector<Edge> readEdges() override;

    virtual ~ObjCarcassReader() override;
};