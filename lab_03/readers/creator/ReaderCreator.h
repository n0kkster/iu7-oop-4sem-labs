#pragma once

#include "../../concepts/concepts.h"
#include "../BaseReader.h"
#include "../model/carcass/CarcassReader.h"

#include <memory>

template <typename BaseReader, typename DerivedReader, typename... Args>
    requires Derivative<DerivedReader, BaseReader> && ConstructibleWith<DerivedReader, Args...>
class ReaderCreator
{
public:
    ReaderCreator() = default;
    ~ReaderCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<DerivedReader> create(CallArgs &&...args);
};

#include "ReaderCreator.hpp"

using CarcassReaderCreator = ReaderCreator<BaseReader, CarcassReader, const std::string &>;
