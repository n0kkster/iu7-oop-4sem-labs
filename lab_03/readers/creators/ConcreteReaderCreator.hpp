#pragma once

#include "ConcreteReaderCreator.h"

template <typename BaseReader, typename DerivedReader>
    requires Derivative<DerivedReader, BaseReader>
std::shared_ptr<BaseReader> ConcreteReaderCreator<BaseReader, DerivedReader>::create(
    const std::string &filename)
{
    return std::make_shared<DerivedReader>(filename);
}
