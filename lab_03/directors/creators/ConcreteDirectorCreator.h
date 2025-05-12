#pragma once

#include "../../readers/camera/CameraReader.h"
#include "../../readers/model/carcass/CarcassReader.h"
#include "../BaseDirector.h"
#include "../model/carcass/CarcassDirector.h"
#include "DirectorCreator.h"
#include "../../concepts/concepts.h"


template <typename BaseDirector, typename DerivedDirector, typename... Args>
    requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
class ConcreteDirectorCreator : public DirectorCreatorTemplate<BaseDirector, Args...>
{
public:
    ConcreteDirectorCreator() = default;
    ~ConcreteDirectorCreator() = default;

    std::shared_ptr<BaseDirector> create(Args &&...args) override;
};

#include "ConcreteDirectorCreator.hpp"

using CarcassDirectorCreator =
    ConcreteDirectorCreator<BaseDirector, CarcassDirector, std::shared_ptr<CarcassReader>>;

// using CameraDirectorCreator =
//     ConcreteDirectorCreator<BaseDirector, CameraDirector, std::shared_ptr<CameraReader>>;

// using CompositeDirectorCreator =
//     ConcreteDirectorCreator<BaseDirector, CompositeDirector, std::shared_ptr<CompositeReader>>;