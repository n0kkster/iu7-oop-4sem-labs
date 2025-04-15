#pragma once

#include "set_node.h"

template <typename Type>
SetNode<Type>::SetNode(const Type &value)
    : SetNode<Type>()
{
    this->data = value;
}

template <typename Type>
SetNode<Type>::SetNode(const std::shared_ptr<SetNode<Type>> &pnode)
    : SetNode<Type>(pnode.data)
{
    this->next = pnode.next;
}

template <typename Type> 
const Type &SetNode<Type>::value() const noexcept
{
    return this->data;
}

template <typename Type>
std::shared_ptr<SetNode<Type>> SetNode<Type>::getNext() const noexcept
{
    return this->next;
}

template <typename Type>
std::shared_ptr<SetNode<Type>> SetNode<Type>::getPrev() const noexcept
{
    return this->prev;
}

template <typename Type>
void SetNode<Type>::set(const Type &value) noexcept
{
    this->data = value;
}

template <typename Type>
void SetNode<Type>::setNull()
{
    this->next = nullptr;
    this->prev = nullptr;
}

template <typename Type>
void SetNode<Type>::setNext(const SetNode<Type> &node)
{
    this->next = std::make_shared<SetNode<Type>>(node);
}

template <typename Type>
void SetNode<Type>::setNext(const std::shared_ptr<SetNode<Type>> &pnode) noexcept
{
    this->next = pnode;
}

template <typename Type>
void SetNode<Type>::setPrev(const SetNode<Type> &node)
{
    this->prev = std::make_shared<SetNode<Type>>(node);
}

template <typename Type>
void SetNode<Type>::setPrev(const std::shared_ptr<SetNode<Type>> &pnode) noexcept
{
    this->prev = pnode;
}

template <typename Type>
bool SetNode<Type>::operator==(const std::shared_ptr<SetNode<Type>> &other) const noexcept
{
    return this == other;
}

template <typename Type>
bool SetNode<Type>::operator!=(const std::shared_ptr<SetNode<Type>> &other) const noexcept
{
    return this != other;
}

template <typename Type>
bool SetNode<Type>::operator<(const std::shared_ptr<SetNode<Type>> &other) const noexcept
{
    return this->data < other->data;
}

template <typename Type>
bool SetNode<Type>::operator>(const std::shared_ptr<SetNode<Type>> &other) const noexcept
{
    return this->data > other->data;
}

template <typename Type>
void SetNode<Type>::exclude()
{
    if (this->next)
        next->prev = prev;

    if (this->prev)
        prev->next = next;

    setNull();
}
