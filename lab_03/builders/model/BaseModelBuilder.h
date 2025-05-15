#pragma once

#include "../../component/primitive/visible/model/BaseModel.h"
#include "../../readers/model/ModelReader.h"
#include "../BaseBuilder.h"

#include <memory>

enum part : size_t
{
    VERTICES = 0,
    EDGES,
    CENTER
};

class BaseModelBuilder : public BaseBuilder
{
protected:
    std::shared_ptr<ModelReader> m_reader;

public:
    BaseModelBuilder() = delete;

    explicit BaseModelBuilder(std::shared_ptr<ModelReader> reader) : m_reader(reader) { }

    virtual ~BaseModelBuilder() override = default;

    virtual bool buildVertices() = 0;
    virtual bool buildEdges() = 0;
    virtual bool buildCenter() = 0;
};
