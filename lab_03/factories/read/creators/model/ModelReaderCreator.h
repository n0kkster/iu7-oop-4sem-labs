#pragma once

#include "../BaseReaderCreator.h"

class ModelReaderCreator : public BaseReaderCreator
{
public:
    ModelReaderCreator() = default;
    virtual ~ModelReaderCreator() override = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) override = 0;
};
