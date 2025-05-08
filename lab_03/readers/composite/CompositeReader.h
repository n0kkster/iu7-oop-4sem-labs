#pragma once

#include "../../component/BaseObject.h"
#include "../BaseReader.h"

#include <memory>
#include <vector>

class CompositeReader : public BaseReader
{
protected:
    std::vector<std::shared_ptr<BaseObject>> m_objects;

    virtual std::shared_ptr<std::vector<std::shared_ptr<BaseObject>>> readObjects() = 0;

public:
    CompositeReader() = delete;
    CompositeReader(const std::string &filename) : BaseReader(filename) { };

    virtual ~CompositeReader() override = default;

    void read(BaseBuilder &builder);

    std::shared_ptr<std::vector<std::shared_ptr<BaseObject>>> getObjects() const;
};
