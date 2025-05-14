#pragma once

#include "../../../concepts/concepts.h"
#include "../BaseCarcassReadStrategy.h"
#include "../txt/TxtCarcassReadStrategy.h"

#include <memory>

template <typename BaseStrategy, typename ConcreteStrategy, typename... Args>
    requires(Derivative<ConcreteStrategy, BaseStrategy>) && (ConstructibleWith<ConcreteStrategy, Args...>)
class CarcassReadStrategyCreator
{
public:
    CarcassReadStrategyCreator() = default;
    ~CarcassReadStrategyCreator() = default;

    std::shared_ptr<ConcreteStrategy> create(Args &&...args);
};

#include "CarcassReadStrategyCreator.hpp"

using CarcassTxtReadStrategyCreator =
    CarcassReadStrategyCreator<BaseCarcassReadStrategy, TxtCarcassReadStrategy,
                               std::shared_ptr<std::ifstream>>;
