#pragma once

#include "ReaderCreator.h"

#include <utility>

template <typename Reader, typename... Args>
    requires ConstructibleWith<Reader, Args...>
template <typename... CallArgs>
    requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<Reader> ReaderCreator<Reader, Args...>::create(CallArgs &&...args)
{
    return std::make_shared<Reader>(std::forward<CallArgs>(args)...);
}
