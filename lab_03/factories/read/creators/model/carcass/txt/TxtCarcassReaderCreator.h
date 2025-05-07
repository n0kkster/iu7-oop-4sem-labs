#pragma once

#include "../CarcassReaderCreator.h"

class TxtCarcassReaderCreator : public CarcassReaderCreator
{
public:
    TxtCarcassReaderCreator() = default;
    virtual ~TxtCarcassReaderCreator() = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) override;
};
