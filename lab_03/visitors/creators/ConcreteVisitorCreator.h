#pragma once

#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../draw/DrawVisitor.h"
#include "../transform/move/MoveVisitor.h"
#include "../transform/rotate/RotateVisitor.h"
#include "../transform/scale/ScaleVisitor.h"
#include "BaseVisitorCreator.h"
#include "../../concepts/concepts.h"

template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor> && ConstructibleWith<DerivedVisitor, Args...>
class ConcreteVisitorCreator : public BaseVisitorCreator<BaseVisitor, Args...>
{
public:
    ConcreteVisitorCreator() = default;
    ~ConcreteVisitorCreator() = default;

    std::shared_ptr<BaseVisitor> create(const Args &...args) override;
};

#include "ConcreteVisitorCreator.hpp"

using RotateVisitorCreator = ConcreteVisitorCreator<BaseVisitor, RotateVisitor, RotationParams>;

using MoveVisitorCreator = ConcreteVisitorCreator<BaseVisitor, MoveVisitor, MoveParams>;

using ScaleVisitorCreator = ConcreteVisitorCreator<BaseVisitor, ScaleVisitor, ScaleParams>;

using DrawVisitorCreator =
    ConcreteVisitorCreator<BaseVisitor, DrawVisitor, std::shared_ptr<BaseProjectionStrategy>,
                           std::shared_ptr<BasePainter>, std::shared_ptr<BaseCamera>>;
