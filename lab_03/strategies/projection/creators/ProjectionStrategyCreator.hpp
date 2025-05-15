#pragma once

#include "ProjectionStrategyCreator.h"

template <typename BaseProjectionStrategy, typename DerivedProjectionStrategy, typename... Args>
    requires Derivative<DerivedProjectionStrategy, BaseProjectionStrategy>
          && ConstructibleWith<DerivedProjectionStrategy, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseProjectionStrategy> ProjectionStrategyCreator<
    BaseProjectionStrategy, DerivedProjectionStrategy, Args...>::create(CallArgs &&...args)
{
    return std::make_shared<DerivedProjectionStrategy>(std::forward<CallArgs>(args)...);
}
