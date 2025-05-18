#pragma once

#include "../../../ids/ids.h"
#include "../ModelDirector.h"

class CarcassDirector : public ModelDirector
{
public:
    CarcassDirector() = delete;
    CarcassDirector(std::shared_ptr<BaseBuilder> builder);

    virtual ~CarcassDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};
