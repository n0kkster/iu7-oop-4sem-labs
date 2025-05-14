#pragma once

#include "CarcassReadStrategyCreator.h"

template <typename BaseStrategy, typename ConcreteStrategy, typename... Args>
    requires(Derivative<ConcreteStrategy, BaseStrategy>) && (ConstructibleWith<ConcreteStrategy, Args...>)
std::shared_ptr<ConcreteStrategy> CarcassReadStrategyCreator<BaseStrategy, ConcreteStrategy, Args...>::create(Args &&...args)
{
    return std::make_shared<ConcreteStrategy>(std::forward<Args>(args)...);
}