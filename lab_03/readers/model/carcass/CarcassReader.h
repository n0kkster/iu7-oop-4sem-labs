#pragma once

#include "../ModelReader.h"

class CarcassReader : public ModelReader
{
public:
    CarcassReader() = delete;
    CarcassReader(const std::string &filename) : ModelReader(filename) { };

    virtual ~CarcassReader() override = default;
};
