#pragma once

#include "../BaseObject.h"

class Primitive : public BaseObject
{
public:
    Primitive() = default;
    virtual ~Primitive() = default;

    bool isComposite() const noexcept override { return false; }
};
