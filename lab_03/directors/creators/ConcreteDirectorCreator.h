#pragma once

#include "DirectorCreator.h"
#include "../../concepts/concepts.h"

template <typename BaseDirector, typename DerivedDirector>
    requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector>
class ConcreteDirectorCreator : public DirectorCreatorTemplate<BaseDirector>
{
public:
    ConcreteDirectorCreator() = default;
    ~ConcreteDirectorCreator() = default;

    std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseReader> reader) override;
};

#include "ConcreteDirectorCreator.hpp"