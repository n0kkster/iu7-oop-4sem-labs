#pragma once

#include "../../concepts/concepts.h"
#include "../ModelReader.h"

template <typename Reader, typename... Args>
    requires ConstructibleWith<Reader, Args...>
class ReaderCreator
{
public:
    ReaderCreator() = default;
    ~ReaderCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<Reader> create(CallArgs &&...args);
};

#include "ReaderCreator.hpp"

using ModelReaderCreator = ReaderCreator<ModelReader, std::shared_ptr<BaseModelReaderImpl>>;
