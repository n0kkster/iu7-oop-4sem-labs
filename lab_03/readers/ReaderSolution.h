#pragma once

#include "../concepts/concepts.h"
#include "../ids/ids.h"
#include "../readers/model/carcass/CarcassReader.h"
#include "BaseReader.h"

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <string>

template <typename... SupportedArgs>
class ReaderSolution
{
    using CreatorFunc = std::function<std::shared_ptr<BaseReader>(const std::tuple<SupportedArgs...> &)>;
    std::map<size_t, CreatorFunc> creators;

public:
    ReaderSolution() = default;
    ~ReaderSolution() = default;

    template <typename Derived, typename... Args>
        requires(IsSupportedArg<Args, SupportedArgs...> && ...)
             && Derivative<Derived, BaseReader> && ConstructibleWith<Derived, Args...>
    void registrate(size_t id);

    template <typename... Args>
        requires(IsSupportedArg<Args, SupportedArgs...> && ...)
    std::shared_ptr<BaseReader> create(size_t id, Args &&...args);
};

using BaseReaderSolution = ReaderSolution<const std::string &>;

#include "ReaderSolution.hpp"
