#pragma once

#include "../concepts/concepts.h"
#include "BaseDirector.h"
#include "creators/ConcreteDirectorCreator.h"
#include "creators/DirectorCreator.h"
#include <initializer_list>

#include <cstddef>
#include <map>
#include <memory>
#include <utility>

class DirectorCreatorMaker
{
public:
    template <Derivative<BaseDirector> ConcreteDirector, typename... Args>
    static std::unique_ptr<BaseDirectorCreator> createDirectorCreator()
        requires Derivative<ConcreteDirector, BaseDirector> && NotAbstract<ConcreteDirector>
              && ConstructibleWith<ConcreteDirector, Args...>
    {
        return std::make_unique<ConcreteDirectorCreator<BaseDirector, ConcreteDirector, Args...>>();
    }
};

class DirectorSolution
{
public:
    using DirectorCreator = std::unique_ptr<BaseDirectorCreator> (&)();
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
