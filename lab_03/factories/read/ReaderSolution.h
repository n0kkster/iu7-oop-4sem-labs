#pragma once

#include "creators/BaseReaderCreator.h"
#include <initializer_list>

#include <cstddef>
#include <map>
#include <memory>

template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = std::is_default_constructible_v<Type>;

class ReaderCreatorMaker
{
public:
    template <Derivative<BaseReaderCreator> ConcreteReaderCreator>
    static std::unique_ptr<BaseReaderCreator> createReaderCreator()
        requires NotAbstract<ConcreteReaderCreator>
    {
        return std::make_unique<ConcreteReaderCreator>();
    }
};

class ReaderSolution
{
public:
    using ReaderCreator = std::unique_ptr<BaseReaderCreator>(&)();
    using CallbackMap = std::map<size_t, ReaderCreator>;

public:
    ReaderSolution() = default;
    ReaderSolution(std::initializer_list<std::pair<size_t, ReaderCreator>> ilist);

    ~ReaderSolution() = default;

    bool registrate(size_t id, ReaderCreator creatorFunc);
    std::unique_ptr<BaseReaderCreator> create(size_t id) const;

private:
    CallbackMap m_callbacks;
};
