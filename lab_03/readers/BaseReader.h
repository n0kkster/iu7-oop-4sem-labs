#pragma once

#include "../builders/BaseBuilder.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

class BaseReader
{
protected:
    std::shared_ptr<std::ifstream> m_file;
    std::string m_filename;

public:
    BaseReader() = delete;
    BaseReader(const std::string &filename) : m_filename(filename) { };

    virtual ~BaseReader() = default;

    virtual void read(BaseBuilder &builder, size_t part) = 0;
};
