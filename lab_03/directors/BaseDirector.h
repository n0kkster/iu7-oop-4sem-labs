#pragma once

#include "../component/BaseObject.h"
#include "../builders/BaseBuilder.h"
#include <memory>

class BaseDirector
{
protected:
    std::shared_ptr<BaseBuilder> m_builder;

public:
    BaseDirector() = delete;
    BaseDirector(std::shared_ptr<BaseBuilder> builder);
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseObject> create() const = 0;
};