#pragma once

#include "../component/BaseObject.h"

#include <cstddef>
#include <memory>

class BaseReader;

class BaseBuilder
{
protected:
    std::shared_ptr<BaseObject> m_product;
    size_t m_part;

    virtual std::shared_ptr<BaseObject> createProduct() = 0;

public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    std::shared_ptr<BaseObject> getProduct();
};
