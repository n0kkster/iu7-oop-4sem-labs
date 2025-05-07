#pragma once

#include "../CarcassReader.h"

class ObjCarcassReader : public CarcassReader
{
public:
    ObjCarcassReader() = delete;
    ObjCarcassReader(const std::string &filename);

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;

    ~ObjCarcassReader() override;
};