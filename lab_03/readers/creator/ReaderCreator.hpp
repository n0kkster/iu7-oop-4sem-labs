#pragma once

#include "ReaderCreator.h"
#include <utility>

template <typename BaseReader, typename DerivedReader, typename... Args>
    requires Derivative<DerivedReader, BaseReader>
          && ConstructibleWith<DerivedReader, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<DerivedReader> ReaderCreator<BaseReader, DerivedReader, Args...>::create(
    CallArgs &&...args)
{
    return std::make_shared<DerivedReader>(std::forward<CallArgs>(args)...);
}
