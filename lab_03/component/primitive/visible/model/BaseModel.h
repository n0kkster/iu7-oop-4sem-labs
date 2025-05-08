#pragma once

#include "../VisibleObject.h"

class BaseModel : public VisibleObject
{
public:
    BaseModel() = default;
    virtual ~BaseModel() override = default;
};
