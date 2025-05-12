#pragma once

#include "../BaseReader.h"

#include <memory>
#include <string>

class BaseReaderCreator
{
public:
    BaseReaderCreator() = default;
    virtual ~BaseReaderCreator() = default;
    
    virtual std::shared_ptr<BaseReader> create(const std::string &filename) = 0;
};

template <typename Reader>
class ReaderCreatorTemplate : public BaseReaderCreator
{
public:
    ReaderCreatorTemplate() = default;
    virtual ~ReaderCreatorTemplate() = default;

    virtual std::shared_ptr<Reader> create(const std::string &filename) = 0;
};
