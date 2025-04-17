#pragma once

#include <cstddef>

class BaseContainer
{

public:
    virtual bool empty() const noexcept = 0;
    virtual size_t size() const noexcept = 0;
    virtual void clear() = 0;
    virtual ~BaseContainer() = default;

protected:
    size_t _size = 0;
};
