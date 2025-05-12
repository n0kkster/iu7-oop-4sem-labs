#pragma once

#include "../ModelDirector.h"
#include "../../../readers/model/carcass/CarcassReader.h"
#include "../../../ids/ids.h"

class CarcassDirector : public ModelDirector
{
public:
    CarcassDirector() = delete;
    CarcassDirector(std::shared_ptr<BaseReader> reader, InternalRepresentation repr);

    virtual ~CarcassDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};