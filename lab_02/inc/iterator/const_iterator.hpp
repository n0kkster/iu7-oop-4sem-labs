#pragma once

#include "const_iterator.h"
#include "exception.h"

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator() noexcept
{
    this->curr.lock() = nullptr;
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<SetNode<T>> &pnode)
{
    this->curr = pnode;
}

template <CopyMoveAssignable T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iter)
{
    checkExpired();

    this->curr = iter.curr.lock();
}

template <CopyMoveAssignable T>
SetNode<T> &ConstIterator<T>::getCurr() const
{
    checkExpired();

    return *this->curr.lock();
}

template <CopyMoveAssignable T>
void ConstIterator<T>::erase() const
{
    this->curr.lock()->exclude();
}

template <CopyMoveAssignable T>
void ConstIterator<T>::next()
{
    checkExpired();

    if (getCurr().getNext() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to increment.");

    this->curr = getCurr().getNext();
}

template <CopyMoveAssignable T>
void ConstIterator<T>::prev()
{
    checkExpired();

    if (getCurr().getPrev() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to decrement.");

    this->curr = getCurr().getPrev();
}

#pragma region Operators

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator++()
{
    checkExpired();

    next();
    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
    checkExpired();

    auto copy = *this;
    next();
    return copy;
}

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator--()
{
    checkExpired();

    prev();
    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T> ConstIterator<T>::operator--(int)
{
    checkExpired();

    auto copy = *this;
    prev();
    return copy;
}

template <CopyMoveAssignable T>
ConstIterator<T> ConstIterator<T>::operator+(int n) const
{
    checkExpired();

    auto copy = *this;
    while (n-- > 0)
        ++copy;

    return copy;
}

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator+=(int n)
{
    checkExpired();

    *this = *this + n;

    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T> ConstIterator<T>::operator-(int n) const
{
    checkExpired();

    auto copy = *this;
    while (n-- > 0)
        --copy;

    return copy;
}

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator-=(int n)
{
    checkExpired();

    *this = *this - n;

    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T>::operator bool() const
{
    checkExpired();

    return this->curr.lock() != nullptr;
}

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &other)
{
    checkExpired();
    other.checkExpired();

    this->curr = other.curr.lock();
    return *this;
}

template <CopyMoveAssignable T>
ConstIterator<T> &ConstIterator<T>::operator=(ConstIterator<T> &&other)
{
    checkExpired();
    other.checkExpired();

    this->curr = std::move(other.curr.lock());
    return *this;
}

template <CopyMoveAssignable T>
const T &ConstIterator<T>::operator*() const
{
    checkExpired();

    return getCurr().value();
}

template <CopyMoveAssignable T>
const T *ConstIterator<T>::operator->() const
{
    checkExpired();

    return &getCurr().value();
}

template <CopyMoveAssignable T>
const T &ConstIterator<T>::operator[](size_t offset) const
{
    checkExpired();
    auto it = this + offset;

    return it.getCurr().value();
}

template <CopyMoveAssignable T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &other) const
{
    checkExpired();
    other.checkExpired();

    return this->curr.lock() == other.curr.lock();
}

template <CopyMoveAssignable T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &other) const
{
    checkExpired();
    other.checkExpired();

    return this->curr.lock() != other.curr.lock();
}

#pragma endregion

template <CopyMoveAssignable T>
void ConstIterator<T>::checkExpired() const
{
    if (this->curr.expired() && this->curr.lock())
        throw new IteratorException("Iterator pointer expired.");
}
