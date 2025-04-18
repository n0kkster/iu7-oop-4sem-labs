#pragma once

#include "const_iterator.h"
#include "exception.h"

template <typename T>
ConstIterator<T>::ConstIterator() noexcept
{
    this->curr.lock() = nullptr;
}

template <typename T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<SetNode<T>> &pnode)
{
    this->curr = pnode;
}

template <typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iter)
{
    checkExpired(__LINE__);

    this->curr = iter.curr.lock();
}

template <typename T>
SetNode<T> &ConstIterator<T>::getCurr() const
{
    checkExpired(__LINE__);

    return *this->curr.lock();
}

template <typename T>
void ConstIterator<T>::erase()
{
    this->curr.lock()->exclude();
}

template <typename T>
void ConstIterator<T>::next()
{
    checkExpired(__LINE__);

    if (getCurr().getNext() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to increment.");

    this->curr = getCurr().getNext();
}

template <typename T>
void ConstIterator<T>::prev()
{
    checkExpired(__LINE__);

    if (getCurr().getPrev() == nullptr)
        throw OutOfRangeException("The iterator went out of bounds while trying to decrement.");

    this->curr = getCurr().getPrev();
}

#pragma region Operators

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator++()
{
    checkExpired(__LINE__);

    next();
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
    checkExpired(__LINE__);

    auto copy = *this;
    next();
    return copy;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator--()
{
    checkExpired(__LINE__);

    prev();
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--(int)
{
    checkExpired(__LINE__);

    auto copy = *this;
    prev();
    return copy;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator+(int n) const
{
    checkExpired(__LINE__);

    auto copy = *this;
    while (n-- > 0)
        ++copy;

    return copy;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator+=(int n)
{
    checkExpired(__LINE__);

    *this = *this + n;

    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator-(int n) const
{
    checkExpired(__LINE__);

    auto copy = *this;
    while (n-- > 0)
        --copy;

    return copy;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator-=(int n)
{
    checkExpired(__LINE__);

    *this = *this - n;

    return *this;
}

template <typename T>
ConstIterator<T>::operator bool() const
{
    checkExpired(__LINE__);

    return this->curr.lock() != nullptr;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &other)
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    this->curr = other.curr.lock();
    return *this;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &&other)
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    this->curr = std::move(other.curr.lock());
    return *this;
}

template <typename T>
const T &ConstIterator<T>::operator*() const
{
    checkExpired(__LINE__);

    return getCurr().value();
}

template <typename T>
const T *ConstIterator<T>::operator->() const
{
    checkExpired(__LINE__);

    return &getCurr().value();
}

template <typename T>
const T &ConstIterator<T>::operator[](size_t offset) const
{
    checkExpired(__LINE__);
    auto it = this + offset;

    return it.getCurr().value();
}

template <typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &other) const
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    return this->curr.lock() == other.curr.lock();
}

template <typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &other) const
{
    checkExpired(__LINE__);
    other.checkExpired(__LINE__);

    return this->curr.lock() != other.curr.lock();
}

#pragma endregion

template <typename T>
void ConstIterator<T>::checkExpired(int line) const
{
    if (this->curr.expired() && this->curr.lock())
        throw new IteratorException("Iterator pointer expired.");
}
