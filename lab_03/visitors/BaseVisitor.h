#pragma once

#include <memory>

class BaseCamera;
class BaseStructure;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(BaseCamera &camera) const = 0;
    virtual void visit(std::shared_ptr<BaseStructure> structure) const = 0;
};