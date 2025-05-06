#pragma once

#include "../primitive.h"

class InvisibleObject : public Primitive
{
public:
    InvisibleObject() = default;
    virtual ~InvisibleObject() = default;

    bool isVisible() const noexcept override { return false; }
};
