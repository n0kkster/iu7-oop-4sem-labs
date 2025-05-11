#pragma once

#include "creators/DirectorCreator.h"
#include <initializer_list>

#include <cstddef>
#include <map>
#include <memory>
#include <utility>


template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = std::is_default_constructible_v<Type>;

class DirectorCreatorMaker
{
public:
    template <Derivative<BaseDirectorCreator> ConcreteDirectorCreator>
    static std::unique_ptr<BaseDirectorCreator> createDirectorCreator()
        requires NotAbstract<ConcreteDirectorCreator>
    {
        return std::make_unique<ConcreteDirectorCreator>();
    }
};

class DirectorSolution
{
public:
    using DirectorCreator = std::unique_ptr<BaseDirectorCreator>(&)();
    using CallbackMap = std::map<size_t, DirectorCreator>;

public:
    DirectorSolution() = default;
    DirectorSolution(std::initializer_list<std::pair<size_t, DirectorCreator>> ilist);

    ~DirectorSolution() = default;

    bool registrate(size_t id, DirectorCreator creatorFunc);
    std::unique_ptr<BaseDirectorCreator> create(size_t id) const;

private:
    CallbackMap m_callbacks;
};
