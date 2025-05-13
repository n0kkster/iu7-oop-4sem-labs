#pragma once

#include "../Primitive.h"

class VisibleObject : public Primitive
{
public:
    VisibleObject() = default;
    virtual ~VisibleObject() override = default;

    bool isVisible() const noexcept override { return true; }
};
