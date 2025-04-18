#pragma once

#include "set_node.h"

template <typename T>
SetNode<T>::SetNode(const T &value)
    : SetNode<T>()
{
    this->data = value;
}

template <typename T>
SetNode<T>::SetNode(T &&value)
    : SetNode<T>()
{
    this->data = std::move(value);
}

template <typename T>
SetNode<T>::SetNode(const std::shared_ptr<SetNode<T>> &pnode)
    : SetNode<T>(pnode.data)
{
    this->next = pnode.next;
}

template <typename T> 
const T &SetNode<T>::value() const noexcept
{
    return this->data;
}

template <typename T>
std::shared_ptr<SetNode<T>> SetNode<T>::getNext() const noexcept
{
    return this->next;
}

template <typename T>
std::shared_ptr<SetNode<T>> SetNode<T>::getPrev() const noexcept
{
    return this->prev;
}

template <typename T>
void SetNode<T>::set(const T &value) noexcept
{
    this->data = value;
}

template <typename T>
void SetNode<T>::setNull()
{
    this->next = nullptr;
    this->prev = nullptr;
}

template <typename T>
void SetNode<T>::setNext(const SetNode<T> &node)
{
    this->next = std::make_shared<SetNode<T>>(node);
}

template <typename T>
void SetNode<T>::setNext(const std::shared_ptr<SetNode<T>> &pnode) noexcept
{
    this->next = pnode;
}

template <typename T>
void SetNode<T>::setNextNull() noexcept
{
    this->next.reset();
}

template <typename T>
void SetNode<T>::setPrev(const SetNode<T> &node)
{
    this->prev = std::make_shared<SetNode<T>>(node);
}

template <typename T>
void SetNode<T>::setPrev(const std::shared_ptr<SetNode<T>> &pnode) noexcept
{
    this->prev = pnode;
}

template <typename T>
void SetNode<T>::setPrevNull() noexcept
{
    this->prev.reset();
}

template <typename T>
bool SetNode<T>::operator==(const std::shared_ptr<SetNode<T>> &other) const noexcept
{
    return this == other;
}

template <typename T>
bool SetNode<T>::operator!=(const std::shared_ptr<SetNode<T>> &other) const noexcept
{
    return this != other;
}

template <typename T>
bool SetNode<T>::operator<(const std::shared_ptr<SetNode<T>> &other) const noexcept
{
    return this->data < other->data;
}

template <typename T>
bool SetNode<T>::operator>(const std::shared_ptr<SetNode<T>> &other) const noexcept
{
    return this->data > other->data;
}

template <typename T>
void SetNode<T>::exclude()
{
    if (this->next)
        next->prev = prev;

    if (this->prev)
        prev->next = next;

    setNull();
}
