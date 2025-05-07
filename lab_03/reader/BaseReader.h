#pragma once

#include <fstream>
#include <string>

class BaseReader
{
protected:
    std::ifstream m_file;
    std::string m_filename;

public:
    BaseReader() = delete;
    BaseReader(const std::string &filename) : m_filename(filename) { };
    virtual ~BaseReader() = default;
};
