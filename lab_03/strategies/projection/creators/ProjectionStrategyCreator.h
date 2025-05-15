#pragma once

#include "../../../concepts/concepts.h"
#include "../BaseProjectionStrategy.h"
#include "../default/DefaultProjectionStrategy.h"

template <typename BaseProjectionStrategy, typename DerivedProjectionStrategy, typename... Args>
    requires Derivative<DerivedProjectionStrategy, BaseProjectionStrategy>
          && ConstructibleWith<DerivedProjectionStrategy, Args...>
class ProjectionStrategyCreator
{
public:
    ProjectionStrategyCreator() = default;
    ~ProjectionStrategyCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseProjectionStrategy> create(CallArgs &&...args);
};

#include "ProjectionStrategyCreator.hpp"

using DefaultProjectionStrategyCreator = ProjectionStrategyCreator<BaseProjectionStrategy, DefaultProjectionStrategy>;
