#pragma once

#include "../primitive.h"

class VisibleObject : public Primitive
{
public:
    VisibleObject() = default;
    virtual ~VisibleObject() = default;

    bool isVisible() const noexcept override { return true; }
};
