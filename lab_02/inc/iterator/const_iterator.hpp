#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "const_iterator.h"

template <typename Type>
ConstIterator<Type>::ConstIterator()
{
    this->curr.lock() = nullptr;
}

template <typename Type>
ConstIterator<Type>::ConstIterator(const std::shared_ptr<SetNode<Type>> &pnode)
{
    this.curr = pnode;
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

    this->curr = getCurr().getNext();
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator++()
{
    checkExpired(__LINE__);

    next();
    return this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    checkExpired(__LINE__);

    ConstIterator<Type> copy = this;
    next();
    return copy;
}

template <typename Type>
void ConstIterator<Type>::prev()
{
    checkExpired(__LINE__);

    this->curr = getCurr().getPrev();
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator--()
{
    checkExpired(__LINE__);

    prev();
    return this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    checkExpired(__LINE__);

    auto copy = this;
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

    auto copy = this;
    while (n --> 0)
        ++copy;
    return copy;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(int n)
{
    checkExpired(__LINE__);

    while (n --> 0)
        ++this;
    return this;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    checkExpired(__LINE__);

    auto copy = this;
    while (n --> 0)
        --copy;
    return copy;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(int n)
{
    checkExpired(__LINE__);

    while (n --> 0)
        --this;
    return this;
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

#include <stdio.h>
template <typename Type>
void ConstIterator<Type>::checkExpired(int line) const
{
    printf("%d\n", line);
    abort();
}

#endif /* CONST_ITERATOR_H */
