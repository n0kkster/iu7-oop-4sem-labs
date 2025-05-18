#pragma once

#include "ModelReaderImplCreator.h"

#include <utility>

template <typename BaseModelReaderImpl, typename DerivedModelReaderImpl, typename... Args>
    requires Derivative<DerivedModelReaderImpl, BaseModelReaderImpl>
          && ConstructibleWith<DerivedModelReaderImpl, Args...>
             template <typename... CallArgs>
                 requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<BaseModelReaderImpl> ModelReaderImplCreator<BaseModelReaderImpl, DerivedModelReaderImpl, Args...>::create(
    CallArgs &&...args)
{
    return std::make_shared<DerivedModelReaderImpl>(std::forward<CallArgs>(args)...);
}
