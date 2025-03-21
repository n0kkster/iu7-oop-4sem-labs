#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <cstddef>

class BaseContainer
{

public:
    // // мб убрать конструкторы и сделать два метода = 0, а деструктор = default?
    // BaseContainer() noexcept {}
    // explicit BaseContainer(const size_t _size) noexcept : size(_size) {}
    // bool isEmpty() const noexcept { return size == 0; };
    // size_t getSize() const noexcept { return size; }
    // virtual ~BaseContainer() = 0;

    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;
    virtual void clear() = 0;
    virtual ~BaseContainer() = default;

protected:
    size_t size = 0;
};

#endif /* BASE_CONTAINER_H */
