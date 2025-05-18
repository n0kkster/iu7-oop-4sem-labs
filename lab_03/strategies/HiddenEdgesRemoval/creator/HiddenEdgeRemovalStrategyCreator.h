#pragma once

#include "../../../concepts/concepts.h"
#include "../BaseHiddenEdgesRemovalStrategy.h"
#include "../raycasting/RaycastingHiddenEdgesRemoval.h"

template <typename BaseHiddenEdgeRemovalStrategy, typename DerivedHiddenEdgeRemovalStrategy, typename... Args>
    requires Derivative<DerivedHiddenEdgeRemovalStrategy, BaseHiddenEdgeRemovalStrategy>
          && ConstructibleWith<DerivedHiddenEdgeRemovalStrategy, Args...>
class HiddenEdgeRemovalStrategyCreator
{
public:
    HiddenEdgeRemovalStrategyCreator() = default;
    ~HiddenEdgeRemovalStrategyCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseHiddenEdgeRemovalStrategy> create(CallArgs &&...args);
};

#include "HiddenEdgeRemovalStrategyCreator.hpp"

using RaycastingHiddenEdgeRemovalStrategyCreator =
    HiddenEdgeRemovalStrategyCreator<BaseHiddenEdgesRemovalStrategy, RaycastingHiddenEdgesRemovalStrategy>;
