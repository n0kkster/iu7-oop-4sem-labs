#pragma once

#include "../../concepts/concepts.h"
#include "../BaseBuilder.h"
#include "../model/carcass/CarcassModelBuilder.h"

#include <memory>

template <typename BaseBuilder, typename DerivedBuilder, typename... Args>
    requires Derivative<DerivedBuilder, BaseBuilder> && ConstructibleWith<DerivedBuilder, Args...>
class BuilderCreator
{
public:
    BuilderCreator() = default;
    ~BuilderCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseBuilder> create(CallArgs &&...args);
};

#include "BuilderCreator.hpp"

using CarcassBuilderCreator =
    BuilderCreator<BaseBuilder, CarcassModelBuilder, std::shared_ptr<ModelReader>, std::shared_ptr<BaseStructure>>;
