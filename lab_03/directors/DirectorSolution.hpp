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
        // Распаковываем кортеж и создаем объект
        return std::apply([](auto &&...args)
                          { return std::make_unique<Derived>(std::forward<decltype(args)>(args)...); }, args);
    };
}

template <typename... SupportedArgs>
template <typename... Args>
    requires(IsSupportedArg<Args, SupportedArgs...> && ...)
std::unique_ptr<BaseDirector> DirectorSolution<SupportedArgs...>::create(size_t id, Args &&...args)
{
    auto it = creators.find(id);
    if (it == creators.end())
        return nullptr;

    // Упаковываем аргументы в кортеж
    auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
    return it->second(args_tuple);
}
