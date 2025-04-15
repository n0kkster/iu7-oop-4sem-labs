#pragma once

#include <concepts>
#include "exception.h"
#include "set.h"

#pragma region ElementAddition

template <typename Type>
bool Set<Type>::add(const std::shared_ptr<SetNode<Type>> &node)
{
    if (this->in(node->value()))
        return false;

    if (this->isEmpty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
        node->setPrev(this->tail);
        this->tail->setNext(node);
        this->tail = node;
    }

    this->_size++;

    return true;
}

template <typename Type>
template <typename T>
requires std::same_as<std::decay_t<T>, Type>
bool Set<Type>::add(T &&value)
{
    if (this->in(value))
        return false;

    std::shared_ptr<SetNode<Type>> newNode;
    try
    {
        newNode = std::make_shared<SetNode<Type>>(std::forward<T>(value));
    }
    catch (const std::bad_alloc &ex)
    {
        throw MemoryException("Error allocating new node!");
    }

    return add(newNode);
}

template <typename Type>
bool Set<Type>::add(const std::initializer_list<Type> list)
{
    for (const Type &el : list)
        if (!this->add(el))
            return false;
    return true;
}

#pragma endregion

#pragma region Iterators

template <typename Type>
ConstIterator<Type> Set<Type>::cbegin() const
{
    return ConstIterator<Type>(this->head);
}

template <typename Type>
ConstIterator<Type> Set<Type>::cend() const
{
    return this->tail ? ConstIterator<Type>(this->tail->getNext()) : ConstIterator<Type>();
}

#pragma endregion

template <typename Type>
bool Set<Type>::isEmpty() const noexcept
{
    return this->_size == 0;
}

template <typename Type>
size_t Set<Type>::size() const noexcept
{
    return this->_size;
}

template <typename Type>
bool Set<Type>::in(const Type &value) const
{
    for (auto it = this->cbegin(); it != this->cend(); ++it)
        if (*it == value)
            return true;
    return false;
}

template <typename Type>
void Set<Type>::clear()
{
    return;
}

template <typename Type>
std::ostream &operator<<(std::ostream &os, const Set<Type> &set)
{
    os << "{";

    for (auto it = set.cbegin(); it != set.cend(); ++it)
        os << *it << ", ";

    os << "}";
    os << "(" << set.size() << ")";

    return os;
}
