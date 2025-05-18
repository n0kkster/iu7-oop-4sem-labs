#pragma once

#include "../../../concepts/concepts.h"
#include "../BaseCoordinateConvertStrategy.h"
#include "../default/DefaultConvertCoordinatesStrategy.h"

#include <memory>

template <typename BaseConvertCoordinatesStrategy, typename DerivedConvertCoordinatesStrategy,
          typename... Args>
    requires Derivative<DerivedConvertCoordinatesStrategy, BaseConvertCoordinatesStrategy>
          && ConstructibleWith<DerivedConvertCoordinatesStrategy, Args...>
class ConvertCoordinatesStrategyCreator
{
public:
    ConvertCoordinatesStrategyCreator() = default;
    ~ConvertCoordinatesStrategyCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseConvertCoordinatesStrategy> create(CallArgs &&...args);
};

#include "ConvertCoordsStrategyCreator.hpp"

using DefaultConvertCoordinatesStrategyCreator =
    ConvertCoordinatesStrategyCreator<BaseCoordinateConvertStrategy, DefaultConvertCoordinateStrategy>;
