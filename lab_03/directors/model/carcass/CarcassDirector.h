#pragma once

#include "../ModelDirector.h"
#include "../../../readers/model/carcass/CarcassReader.h"
#include "../../../ids/ids.h"

class CarcassDirector : public ModelDirector
{
public:
    CarcassDirector() = delete;
    CarcassDirector(const std::string &filename, InternalRepresentationId repr);

    virtual ~CarcassDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};