#pragma once

#include "../ModelReaderCreator.h"

class CarcassReaderCreator : public ModelReaderCreator
{
public:
    CarcassReaderCreator() = default;
    virtual ~CarcassReaderCreator() override = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) override = 0;
};
