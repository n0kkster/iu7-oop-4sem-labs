#pragma once

#include "BaseReaderCreator.h"
#include "../../concepts/concepts.h"


template <typename BaseReader, typename DerivedReader>
    requires Derivative<DerivedReader, BaseReader>
class ConcreteReaderCreator : public ReaderCreatorTemplate<BaseReader>
{
public:
    ConcreteReaderCreator() = default;
    ~ConcreteReaderCreator() = default;

    std::shared_ptr<BaseReader> create(const std::string &filename) override;
};

#include "ConcreteReaderCreator.hpp"