#pragma once

#include "../BaseReaderCreator.h"

class ModelReaderCreator : public BaseReaderCreator
{
public:
    ModelReaderCreator() = default;
    virtual ~ModelReaderCreator() = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) = 0;
};
