#pragma once

#include "../BaseModelReaderImpl.h"

class CsvModelReaderImpl : public BaseModelReaderImpl
{
public:
    CsvModelReaderImpl() = delete;
    CsvModelReaderImpl(const std::string &filename);
    virtual ~CsvModelReaderImpl() override = default;

    std::shared_ptr<std::vector<Vertex>> readVertices() override;
    std::shared_ptr<std::vector<Edge>> readEdges() override;
};
