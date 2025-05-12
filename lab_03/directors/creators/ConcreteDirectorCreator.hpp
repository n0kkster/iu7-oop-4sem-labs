#pragma once

#include "ConcreteDirectorCreator.h"

template <typename BaseDirector, typename DerivedDirector, typename... Args>
    requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
std::shared_ptr<BaseDirector> ConcreteDirectorCreator<BaseDirector, DerivedDirector, Args...>::create(
    Args &&...args)
{
    return std::make_shared<DerivedDirector>(std::forward<Args>(args)...);
}
