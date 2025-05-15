#pragma once

#include "HiddenEdgeRemovalStrategyCreator.h"

template <typename BaseHiddenEdgeRemovalStrategy, typename DerivedHiddenEdgeRemovalStrategy, typename... Args>
    requires Derivative<DerivedHiddenEdgeRemovalStrategy, BaseHiddenEdgeRemovalStrategy>
          && ConstructibleWith<DerivedHiddenEdgeRemovalStrategy, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseHiddenEdgeRemovalStrategy> HiddenEdgeRemovalStrategyCreator<
    BaseHiddenEdgeRemovalStrategy, DerivedHiddenEdgeRemovalStrategy, Args...>::create(CallArgs &&...args)
{
    return std::make_shared<DerivedHiddenEdgeRemovalStrategy>(std::forward<CallArgs>(args)...);
}
