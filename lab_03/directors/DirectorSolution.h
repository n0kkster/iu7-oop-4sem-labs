#pragma once

#include "../concepts/concepts.h"
#include "../readers/model/carcass/CarcassReader.h"
#include "BaseDirector.h"
#include "creators/ConcreteDirectorCreator.h"
#include "creators/DirectorCreator.h"

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <utility>
#include <variant>

// class DirectorCreatorMaker
// {
// public:
//     template <Derivative<BaseDirector> ConcreteDirector, typename... Args>
//     static std::unique_ptr<BaseDirectorCreator> createDirectorCreator()
//         requires Derivative<ConcreteDirector, BaseDirector> && NotAbstract<ConcreteDirector>
//               && ConstructibleWith<ConcreteDirector, Args...>
//     {
//         return std::make_unique<ConcreteDirectorCreator<BaseDirector, ConcreteDirector, Args...>>();
//     }
// };

// class CreatorContainer
// {
// public:
//     template <typename... Args>
//     CreatorContainer(std::unique_ptr<BaseDirectorCreator<Args...>> creator) :
//         m_invoke([creator = std::move(creator)](auto &&...args)
//                  { return creator->create(std::forward<decltype(args)>(args)...); })
//     { }

//     template <typename... Args>
//     std::shared_ptr<BaseDirector> create(Args &&...args) const
//     {
//         return m_invoke(std::forward<Args>(args)...);
//     }

// private:
//     std::function<std::shared_ptr<BaseDirector>(auto &&...)> m_invoke;
// };

// class DirectorCreatorMaker
// {
// public:
//     template <Derivative<BaseDirector> ConcreteDirector, typename... Args>
//     static std::unique_ptr<BaseDirector> createDirectorCreator()
//         requires Derivative<ConcreteDirector, BaseDirector> && NotAbstract<ConcreteDirector>
//               && ConstructibleWith<ConcreteDirector, Args...>
//     {
//         return std::make_unique<BaseDirectorCreator::create<ConcreteDirector>>();
//     }
// };

// class DirectorSolution
// {
// public:
//     // using DirectorCreator = std::unique_ptr<BaseDirector> (&)();
//     using DirectorCreator = std::function<std::unique_ptr<BaseDirector>()>;
//     using CallbackMap = std::map<size_t, DirectorCreator>;

// private:
//     CallbackMap m_callbacks;

// public:
//     DirectorSolution() = default;
//     DirectorSolution(std::initializer_list<std::pair<size_t, DirectorCreator>> ilist);

//     ~DirectorSolution() = default;

//     bool registrate(size_t id, DirectorCreator creatorFunc);
//     DirectorCreator create(size_t id) const;
// };

// template <typename... SupportedArgs>
// class DirectorSolution
// {
// private:
//     using CreatorVariant = std::variant<
//         std::function<std::unique_ptr<BaseDirector>(std::shared_ptr<BaseReader>, InternalRepresentation)>>;

//     std::map<size_t, CreatorVariant> m_creators;

// public:
//     DirectorSolution() = default;
//     ~DirectorSolution() = default;

//     template <typename Derived, typename... Args>
//         requires(IsSupportedArg<Args, SupportedArgs...> && ...)
//              && Derivative<Derived, BaseDirector> && ConstructibleWith<Derived, Args...>
//     void registrate(size_t id);

//     template <typename... Args>
//         requires(IsSupportedArg<Args, SupportedArgs...> && ...)
//     std::unique_ptr<BaseDirector> create(size_t id, Args &&...args) const;

//     // template <typename... Args>
//     //     requires(IsSupportedArg<Args, SupportedArgs...> && ...)
//     // std::unique_ptr<BaseDirector> create_strict(size_t id, Args &&...args) const;
// };

// using BaseDirectorSolution = DirectorSolution<std::shared_ptr<BaseReader>, InternalRepresentation>;

// #include "DirectorSolution.hpp"

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
