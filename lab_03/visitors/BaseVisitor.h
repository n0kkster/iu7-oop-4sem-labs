#pragma once

class BaseCamera;
class CarcassModel;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(BaseCamera &camera) const = 0;
    virtual void visit(CarcassModel &model) const = 0;
};