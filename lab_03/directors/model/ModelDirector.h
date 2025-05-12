#pragma once

#include "../BaseDirector.h"
#include <string>

class ModelDirector : public BaseDirector
{
public:
    ModelDirector() = default;
    virtual ~ModelDirector() = default;

    virtual std::shared_ptr<BaseObject> create() const = 0;
};