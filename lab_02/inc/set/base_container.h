#pragma once

#include <cstddef>

class BaseContainer
{

public:
    virtual bool isEmpty() const noexcept = 0;
    virtual size_t getSize() const noexcept = 0;
    virtual void clear() = 0;
    virtual ~BaseContainer() = default;

protected:
    size_t size = 0;
};
