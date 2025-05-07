#pragma once

#include "../ModelReaderCreator.h"

class CarcassReaderCreator : public ModelReaderCreator
{
public:
    CarcassReaderCreator() = default;
    virtual ~CarcassReaderCreator() = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) = 0;
};
