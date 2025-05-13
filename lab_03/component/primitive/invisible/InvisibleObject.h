#pragma once

#include "../Primitive.h"

class InvisibleObject : public Primitive
{
public:
    InvisibleObject() = default;
    virtual ~InvisibleObject() override = default;

    bool isVisible() const noexcept override { return false; }
};
