#pragma once

#include "../BaseDirector.h"
#include "../../builders/BaseBuilder.h"

#include <memory>

class BaseDirectorCreator
{
public:
    BaseDirectorCreator() = default;
    virtual ~BaseDirectorCreator() = default;

    virtual std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseBuilder> builder) = 0;
};

