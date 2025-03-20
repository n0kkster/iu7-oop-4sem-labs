#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <cstddef>

class BaseContainer
{
public:
    BaseContainer() noexcept : size(0) {}
    BaseContainer(const size_t _size) noexcept : size(_size) {}
    bool isEmpty() const noexcept { return size == 0; };
    size_t getSize() const noexcept { return size; }
    virtual ~BaseContainer() = default;

protected:
    size_t size;
};

#endif /* BASE_CONTAINER_H */
