#pragma once

#include "../../concepts/concepts.h"
#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../draw/DrawVisitor.h"
#include "../transform/move/MoveVisitor.h"
#include "../transform/rotate/RotateVisitor.h"
#include "../transform/scale/ScaleVisitor.h"
#include "BaseVisitorCreator.h"

template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor> && ConstructibleWith<DerivedVisitor, Args...>
class ConcreteVisitorCreator : public BaseVisitorCreator<BaseVisitor, Args...>
{
public:
    ConcreteVisitorCreator() = default;
    ~ConcreteVisitorCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    std::shared_ptr<BaseVisitor> create(CallArgs &&...args);
};

#include "ConcreteVisitorCreator.hpp"

using RotateVisitorCreator = ConcreteVisitorCreator<BaseVisitor, RotateVisitor, RotationParams>;

using MoveVisitorCreator = ConcreteVisitorCreator<BaseVisitor, MoveVisitor, MoveParams>;

using ScaleVisitorCreator = ConcreteVisitorCreator<BaseVisitor, ScaleVisitor, ScaleParams>;

using DrawVisitorCreator =
    ConcreteVisitorCreator<BaseVisitor, DrawVisitor, std::shared_ptr<BaseProjectionStrategy>,
                           std::shared_ptr<BasePainter>, std::shared_ptr<BaseCamera>>;
