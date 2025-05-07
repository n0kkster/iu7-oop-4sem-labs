#pragma once

#include "../../../readers/BaseReader.h"

#include <memory>
#include <string>

class BaseReaderCreator
{
public:
    BaseReaderCreator() = default;
    virtual ~BaseReaderCreator() = default;

    virtual std::shared_ptr<BaseReader> create(const std::string &filename) = 0;
};
