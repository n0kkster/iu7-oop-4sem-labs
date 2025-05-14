#pragma once
#include "DirectorSolution.h"

template <typename... SupportedArgs>
template <typename Derived, typename... Args>
    requires(IsSupportedArg<Args, SupportedArgs...> && ...)
         && Derivative<Derived, BaseDirector> && ConstructibleWith<Derived, Args...>
void DirectorSolution<SupportedArgs...>::registrate(size_t id)
{
    creators[id] = [](const std::tuple<SupportedArgs...> &args)
    {
        return std::apply([](auto &&...args)
                          { return std::make_unique<Derived>(std::forward<decltype(args)>(args)...); }, args);
    };
}

template <typename... SupportedArgs>
template <typename... Args>
    requires(IsSupportedArg<Args, SupportedArgs...> && ...)
std::unique_ptr<BaseDirector> DirectorSolution<SupportedArgs...>::create(size_t id, Args &&...args)
{
    if (auto it = creators.find(id); it != creators.end())
        return it->second(std::make_tuple(std::forward<Args>(args)...));

    return nullptr; // mb throw?
}
