#pragma once

#include "ConvertCoordsStrategyCreator.h"

template <typename BaseConvertCoordinatesStrategy, typename DerivedConvertCoordinatesStrategy,
          typename... Args>
    requires Derivative<DerivedConvertCoordinatesStrategy, BaseConvertCoordinatesStrategy>
          && ConstructibleWith<DerivedConvertCoordinatesStrategy, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseConvertCoordinatesStrategy> ConvertCoordinatesStrategyCreator<
    BaseConvertCoordinatesStrategy, DerivedConvertCoordinatesStrategy, Args...>::create(CallArgs &&...args)
{
    return std::make_shared<DerivedConvertCoordinatesStrategy>(std::forward<CallArgs>(args)...);
}
