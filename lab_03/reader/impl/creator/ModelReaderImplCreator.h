#pragma once
#include "../../../concepts/concepts.h"
#include "../csv/CsvModelReaderImpl.h"
#include "../obj/ObjModelReaderImpl.h"
#include "../txt/TxtModelReaderImpl.h"

template <typename BaseModelReaderImpl, typename DerivedModelReaderImpl, typename... Args>
    requires Derivative<DerivedModelReaderImpl, BaseModelReaderImpl> && ConstructibleWith<DerivedModelReaderImpl, Args...>
class ModelReaderImplCreator
{
public:
    ModelReaderImplCreator() = default;
    ~ModelReaderImplCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseModelReaderImpl> create(CallArgs &&...args);
};

#include "ModelReaderImplCreator.hpp"

using TxtModelReaderImplCreator = ModelReaderImplCreator<BaseModelReaderImpl, TxtModelReaderImpl, const std::string &>;
using CsvModelReaderImplCreator = ModelReaderImplCreator<BaseModelReaderImpl, CsvModelReaderImpl, const std::string &>;
using ObjModelReaderImplCreator = ModelReaderImplCreator<BaseModelReaderImpl, ObjModelReaderImpl, const std::string &>;
