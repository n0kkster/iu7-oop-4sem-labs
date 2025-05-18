#pragma once

#include "../builders/BaseBuilder.h"
#include "../component/BaseObject.h"

#include <memory>

class BaseDirector
{
protected:
    std::shared_ptr<BaseBuilder> m_builder;

public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseObject> create() const = 0;
};
