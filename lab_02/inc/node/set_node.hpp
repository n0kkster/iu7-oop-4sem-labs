#pragma once

#include "concepts.h"
#include "set.h"

template <CopyMoveAssignable T>
Set<T>::SetNode::SetNode(const T &value) noexcept : data(value), next(nullptr)
{ }

template <CopyMoveAssignable T>
Set<T>::SetNode::SetNode(T &&value) noexcept : data(std::move(value)), next(nullptr)
{ }

template <CopyMoveAssignable T>
Set<T>::SetNode::SetNode(const std::shared_ptr<typename Set<T>::SetNode> curr, const T &value) noexcept :
    next(curr), data(value)
{ }

template <CopyMoveAssignable T>
template <typename... Args>
std::shared_ptr<typename Set<T>::SetNode> Set<T>::SetNode::create(Args &&...params)
{
    struct Enable_make_shared : public Set<T>::SetNode
    {
        Enable_make_shared(Args &&...args) : Set<T>::SetNode(std::forward<Args>(args)...) { }
    };

    return std::make_shared<Enable_make_shared>(std::forward<Args>(params)...);
}

template <CopyMoveAssignable T>
const T &Set<T>::SetNode::value() const noexcept
{
    return this->data;
}

template <CopyMoveAssignable T>
std::shared_ptr<T> Set<T>::SetNode::get()
{
    std::shared_ptr<SetNode> tmp = this->shared_from_this();
    return { tmp, &tmp->data };
}

template <CopyMoveAssignable T>
std::shared_ptr<typename Set<T>::SetNode> Set<T>::SetNode::getNext() const noexcept
{
    return this->next;
}

template <CopyMoveAssignable T>
void Set<T>::SetNode::set(const T &value) noexcept
{
    this->data = value;
}

template <CopyMoveAssignable T>
void Set<T>::SetNode::setNull() noexcept
{
    this->next = nullptr;
}

template <CopyMoveAssignable T>
void Set<T>::SetNode::setNext(const typename Set<T>::SetNode &node)
{
    try
    {
        this->next = std::make_shared<typename Set<T>::SetNode>(node);
    }
    catch (const std::bad_alloc &ex)
    {
        throw MemoryException("Error allocating memory for next!");
    }
}

template <CopyMoveAssignable T>
void Set<T>::SetNode::setNext(const std::shared_ptr<typename Set<T>::SetNode> &pnode) noexcept
{
    this->next = pnode;
}

template <CopyMoveAssignable T>
void Set<T>::SetNode::setNextNull() noexcept
{
    this->next.reset();
}

template <CopyMoveAssignable T>
bool Set<T>::SetNode::operator==(const std::shared_ptr<typename Set<T>::SetNode> &other) const noexcept
{
    return this->data == other->data && this->next == other->next;
}

template <CopyMoveAssignable T>
bool Set<T>::SetNode::operator!=(const std::shared_ptr<typename Set<T>::SetNode> &other) const noexcept
{
    return this->data != other->data || this->next != other->next;
}
