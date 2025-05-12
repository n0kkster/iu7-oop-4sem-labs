#pragma once

#include "ConcreteDirectorCreator.h"

template <typename BaseDirector, typename DerivedDirector>
    requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector>
std::shared_ptr<BaseDirector> ConcreteDirectorCreator<BaseDirector, DerivedDirector>::create(
    std::shared_ptr<BaseReader> reader)
{
    return std::make_shared<DerivedDirector>(reader);
}
