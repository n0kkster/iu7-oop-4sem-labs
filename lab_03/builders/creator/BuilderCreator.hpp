#pragma once

#include "BuilderCreator.h"

#include <utility>

template <typename BaseBuilder, typename DerivedBuilder, typename... Args>
    requires Derivative<DerivedBuilder, BaseBuilder>
          && ConstructibleWith<DerivedBuilder, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseBuilder> BuilderCreator<BaseBuilder, DerivedBuilder, Args...>::create(
    CallArgs &&...args)
{
    return std::make_shared<DerivedBuilder>(std::forward<CallArgs>(args)...);
}
