#pragma once

#include "../ModelDirector.h"
#include "../../../readers/model/carcass/CarcassReader.h"

class CarcassDirector : public ModelDirector
{
public:
    CarcassDirector() = delete;
    CarcassDirector(std::shared_ptr<CarcassReader> reader);

    virtual ~CarcassDirector() = default;

    std::shared_ptr<BaseObject> create() const override;
};