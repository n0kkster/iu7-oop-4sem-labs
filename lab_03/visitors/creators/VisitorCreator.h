#pragma once

#include "../../concepts/concepts.h"
#include "../../strategies/projection/BaseProjectionStrategy.h"
#include "../draw/DrawVisitor.h"
#include "../transform/move/MoveVisitor.h"
#include "../transform/rotate/RotateVisitor.h"
#include "../transform/scale/ScaleVisitor.h"

template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor> && ConstructibleWith<DerivedVisitor, Args...>
class VisitorCreator
{
public:
    VisitorCreator() = default;
    ~VisitorCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseVisitor> create(CallArgs &&...args);
};

#include "VisitorCreator.hpp"

using RotateVisitorCreator = VisitorCreator<BaseVisitor, RotateVisitor, RotationParams>;

using MoveVisitorCreator = VisitorCreator<BaseVisitor, MoveVisitor, MoveParams>;

using ScaleVisitorCreator = VisitorCreator<BaseVisitor, ScaleVisitor, ScaleParams>;

using DrawVisitorCreator =
    VisitorCreator<BaseVisitor, DrawVisitor, std::shared_ptr<BaseProjectionStrategy>,
                           std::shared_ptr<BasePainter>, std::shared_ptr<BaseCamera>>;
