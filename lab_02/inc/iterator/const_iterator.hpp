#pragma once

#include "exception.h"
#include "const_iterator.h"

template <typename Type>
ConstIterator<Type>::ConstIterator() noexcept
{
    this->curr.lock() = nullptr;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const std::shared_ptr<SetNode<Type>> &pnode)
{
    this->curr = pnode;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iter)
{
    checkExpired(__LINE__);

    this->curr = iter.curr.lock();
}

template <typename Type>
SetNode<Type> &ConstIterator<Type>::getCurr() const
{
    checkExpired(__LINE__);

    return *this->curr.lock();
}

template <typename Type>
void ConstIterator<Type>::next()
{
    checkExpired(__LINE__);

    if (getCurr().getNext() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to increment.");

    this->curr = getCurr().getNext();
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator++()
{
    checkExpired(__LINE__);

    next();
    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    checkExpired(__LINE__);

    auto copy = *this;
    next();
    return copy;
}

template <typename Type>
void ConstIterator<Type>::prev()
{
    checkExpired(__LINE__);

    if (getCurr().getPrev() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to decrement.");

    this->curr = getCurr().getPrev();
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator--()
{
    checkExpired(__LINE__);

    prev();
    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    checkExpired(__LINE__);

    auto copy = *this;
    prev();
    return copy;
}

template <typename Type>
ConstIterator<Type>::operator bool() const
{
    checkExpired(__LINE__);

    return this->curr.lock() != nullptr;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int n) const
{
    checkExpired(__LINE__);

    auto copy = *this;
    while (n --> 0)
        ++copy;

    return copy;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(int n)
{
    checkExpired(__LINE__);

    *this = *this + n;

    return *this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    checkExpired(__LINE__);

    auto copy = *this;
    while (n --> 0)
        --copy;

    return copy;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(int n)
{
    checkExpired(__LINE__);

    *this = *this - n;
    
    return *this;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const ConstIterator<Type> &other)
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    this->curr = other.curr.lock();
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const ConstIterator<Type> &&other)
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    this->curr = other.curr.lock();
}

template <typename Type>
const Type &ConstIterator<Type>::operator*() const
{
    checkExpired(__LINE__);

    return getCurr().value();
}

template <typename Type>
const Type *ConstIterator<Type>::operator->() const
{
    checkExpired(__LINE__);

    return &getCurr().value();
}

template <typename Type>
const Type &ConstIterator<Type>::operator[](size_t offset) const
{
    checkExpired(__LINE__);
    auto it = this + offset;

    return it.getCurr().value();
}

template <typename Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type> &other) const
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    return this->curr.lock() == other.curr.lock();
}

template <typename Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type> &other) const
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    return this->curr.lock() != other.curr.lock();
}

template <typename Type>
void ConstIterator<Type>::checkExpired(int line) const
{
    if (this->curr.expired() && this->curr.lock())
        throw new IteratorException("Iterator pointer expired.");
}
