#pragma once

#include "../component/BaseObject.h"

#include <cstddef>
#include <memory>

class BaseReader;

class BaseBuilder
{
protected:
    std::shared_ptr<BaseObject> m_product;
    std::shared_ptr<BaseReader> m_reader;
    size_t m_part;

    virtual std::shared_ptr<BaseObject> createProduct() = 0;

public:
    BaseBuilder() = delete;
    explicit BaseBuilder(std::shared_ptr<BaseReader> reader);

    virtual ~BaseBuilder() = default;

    std::shared_ptr<BaseObject> getProduct();
};
