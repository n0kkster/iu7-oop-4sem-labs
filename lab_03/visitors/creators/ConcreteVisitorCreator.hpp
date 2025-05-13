#pragma once

#include "ConcreteVisitorCreator.h"

template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor> && ConstructibleWith<DerivedVisitor, Args...>
std::shared_ptr<BaseVisitor> ConcreteVisitorCreator<BaseVisitor, DerivedVisitor, Args...>::create(
    const Args &...args)
{
    return std::make_shared<DerivedVisitor>(std::forward<Args>(args)...);
}
