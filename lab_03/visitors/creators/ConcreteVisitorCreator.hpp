#pragma once

#include "ConcreteVisitorCreator.h"

#include <utility>

template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor>
          && ConstructibleWith<DerivedVisitor, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseVisitor> ConcreteVisitorCreator<BaseVisitor, DerivedVisitor, Args...>::create(
    CallArgs &&...args)
{
    return std::make_shared<DerivedVisitor>(std::forward<CallArgs>(args)...);
}
