#pragma once

#include "../concepts/concepts.h"
#include "../ids/ids.h"
#include "../readers/model/carcass/CarcassReader.h"
#include "BaseDirector.h"

#include <cstddef>
#include <functional>
#include <map>
#include <memory>

template <typename... SupportedArgs>
class DirectorSolution
{
    using CreatorFunc = std::function<std::unique_ptr<BaseDirector>(const std::tuple<SupportedArgs...> &)>;
    std::map<size_t, CreatorFunc> creators;

public:
    DirectorSolution() = default;
    ~DirectorSolution() = default;

    template <typename Derived, typename... Args>
        requires(IsSupportedArg<Args, SupportedArgs...> && ...)
             && Derivative<Derived, BaseDirector> && ConstructibleWith<Derived, Args...>
    void registrate(size_t id);

    template <typename... Args>
        requires(IsSupportedArg<Args, SupportedArgs...> && ...)
    std::unique_ptr<BaseDirector> create(size_t id, Args &&...args);
};

using BaseDirectorSolution = DirectorSolution<std::shared_ptr<BaseReader>, InternalRepresentation>;

#include "DirectorSolution.hpp"
