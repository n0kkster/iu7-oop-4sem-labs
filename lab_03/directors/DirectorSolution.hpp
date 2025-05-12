// #pragma once

// #include "DirectorSolution.h"

// // DirectorSolution::DirectorSolution(std::initializer_list<std::pair<size_t, DirectorCreator>> ilist)
// // {
// //     for (auto &&p : ilist)
// //         registrate(p.first, p.second);
// // }

// // template <typename... SupportedArgs>
// // template <typename... Args>
// //     requires (IsSupportedArg<Args, SupportedArgs...> && ...)
// // bool DirectorSolution::registrate(size_t id)
// // {
// //     return m_callbacks.insert(CallbackMap::value_type(id, creatorFunc)).second;
// // }

// // DirectorSolution::DirectorCreator DirectorSolution::create(size_t id) const
// // {
// //     auto it = m_callbacks.find(id);

// //     // if (it == m_callbacks.end())
// //         // return nullptr;

// //     return it->second;
// // }

// // Реализация registrate
// template <typename... SupportedArgs>
// template <typename Derived, typename... Args>
//     requires(IsSupportedArg<Args, SupportedArgs...> && ...)
//          && Derivative<Derived, BaseDirector> && ConstructibleWith<Derived, Args...>
// void DirectorSolution<SupportedArgs...>::registrate(size_t id)
// {
//     m_creators[id] = ([](Args... args) -> std::unique_ptr<BaseDirector>
//     {
//         return std::make_unique<Derived>(args...);
//     });
// }

// // Реализация create
// template <typename... SupportedArgs>
// template <typename... Args>
//     requires(IsSupportedArg<Args, SupportedArgs...> && ...)
// std::unique_ptr<BaseDirector> DirectorSolution<SupportedArgs...>::create(size_t id, Args &&...args) const
// {
//     auto it = m_creators.find(id);
//     if (it == m_creators.end())
//         return nullptr;

//     using FuncType = std::function<std::unique_ptr<BaseDirector>(Args...)>;

//     if (auto *func = std::get_if<FuncType>(&it->second))
//     {
//         return (*func)(std::forward<Args>(args)...);
//     }

//     return nullptr;
// }

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
