#pragma once

#include "../BaseVisitor.h"

class DrawVisitor : public BaseVisitor
{
public:
    DrawVisitor() = default;
    virtual ~DrawVisitor() override = default;
};