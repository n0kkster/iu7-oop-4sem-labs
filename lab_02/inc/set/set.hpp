#pragma once

#include "exception.h"
#include "set.h"

#include <algorithm>
#include <iostream>

#pragma region Constructors

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T>::Set(const size_t size, const U *array) : Set()
{
    // std::cout << "arr cctor called\n";
    std::ranges::for_each(array, array + size, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T>::Set(std::initializer_list<U> ilist) : Set()
{
    // std::cout << "ilist cctor called\n";
    std::ranges::for_each(ilist, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(const Set<T> &other) : Set()
{
    // std::cout << "copy cctor called\n";
    std::ranges::for_each(other, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(Set<T> &&other) noexcept
{
    // std::cout << "move cctor called\n";

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    other._size = 0;
}

template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
Set<T>::Set(const It &begin, const It &end)
{
    // std::cout << "iter cctor called\n";
    std::ranges::for_each(begin, end, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(const C &container)
{
    std::cout << "called container cctor\n";
    std::ranges::for_each(container, [this](const T &value) { this->add(value); });
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(const R &range)
{
    std::cout << "called range cctor\n";
    std::ranges::for_each(range, [this](const T &value) { this->add(value); });
}

#pragma endregion

#pragma region Add

template <CopyMoveAssignable T>
bool Set<T>::add(const std::shared_ptr<SetNode<T>> &node)
{
    if (this->in(node->value()))
        return false;

    if (this->empty())
    {
        std::shared_ptr<SetNode<T>> after_last, before_first;
        try
        {
            after_last = std::make_shared<SetNode<T>>();
            before_first = std::make_shared<SetNode<T>>();
        }
        catch (const std::bad_alloc &ex)
        {
            throw MemoryException("Error allocating edge nodes!");
        }

        this->head = node;
        this->tail = node;

        after_last->setPrev(this->tail);
        this->tail->setNext(after_last);

        before_first->setNext(this->head);
        this->head->setPrev(before_first);
    }
    else
    {
        node->setPrev(this->tail);
        node->setNext(this->tail->getNext());

        this->tail->getNext()->setPrev(node);

        this->tail->setNext(node);
        this->tail = node;
    }

    this->_size++;

    return true;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::add(const U &value)
{
    if (this->in(value))
        return false;

    std::shared_ptr<SetNode<T>> newNode;
    try
    {
        newNode = std::make_shared<SetNode<T>>(value);
    }
    catch (const std::bad_alloc &ex)
    {
        throw MemoryException("Error allocating new node!");
    }

    return add(newNode);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::add(U &&value)
{
    if (this->in(value))
        return false;

    std::shared_ptr<SetNode<T>> newNode;
    try
    {
        newNode = std::make_shared<SetNode<T>>(std::move(value));
    }
    catch (const std::bad_alloc &ex)
    {
        throw MemoryException("Error allocating new node!");
    }

    return add(newNode);
}

#pragma endregion

#pragma region Erase

template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
bool Set<T>::erase(It &pos)
{
    if (this->head == this->tail)
    {
        this->clear();
        return true;
    }

    if (pos == this->cend())
        return false;

    auto it_copy = pos + 1;

    if (pos == this->cbegin())
    {
        auto temp = this->head;
        this->head = this->head->getNext();
        temp->exclude();
    }
    else if (pos == this->cend() - 1)
    {
        auto temp = this->tail;
        this->tail = this->tail->getPrev();
        temp->exclude();
    }
    else
        pos.erase();

    pos = it_copy;
    --_size;

    return true;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::erase(const U &value)
{
    ConstIterator<T> it = this->find(value);
    if (it == this->cend())
        return false;

    this->erase(it);
    return true;
}

#pragma endregion

#pragma region Iterators

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::cbegin() const noexcept
{
    return ConstIterator<T>(this->head);
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::cend() const noexcept
{
    return this->tail ? ConstIterator<T>(this->tail->getNext()) : ConstIterator<T>();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::begin() const noexcept
{
    return this->cbegin();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::end() const noexcept
{
    return this->cend();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::crbegin() const noexcept
{
    return this->cbegin();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::crend() const noexcept
{
    return this->cend();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::rbegin() const noexcept
{
    return this->begin();
}

template <CopyMoveAssignable T>
ConstIterator<T> Set<T>::rend() const noexcept
{
    return this->end();
}

#pragma endregion

#pragma region Misc

template <CopyMoveAssignable T>
bool Set<T>::empty() const noexcept
{
    return this->_size == 0;
}

template <CopyMoveAssignable T>
void Set<T>::clear()
{
    while (this->head)
    {
        auto temp = this->head;
        this->head = this->head->getNext();
        temp->setNextNull();
        temp->setPrevNull();
    }

    this->tail.reset();
    this->_size = 0;
}

template <CopyMoveAssignable T>
size_t Set<T>::size() const noexcept
{
    return this->_size;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::subsetOf(const Set<U> &other) const
{
    for (const auto &el : *this)
        if (!other.in(el))
            return false;

    return true;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::supersetOf(const Set<U> &other) const
{
    return other.subsetOf(*this);
}

#pragma endregion

#pragma region Find

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::in(const U &value) const noexcept
{
    return this->find(value) != this->cend();
}

template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It>
bool Set<T>::in(const It &it) const noexcept
{
    return this->in(*it);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
ConstIterator<T> Set<T>::find(const U &value) const noexcept
{
    return std::ranges::find(*this, value);
}

#pragma endregion

#pragma region Operators

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::assign(const Set<U> &other)
{
    if (&other == this)
        return *this;

    // this->clear();
    // for (const auto &el : other)
    // this->add(el);
    std::ranges::for_each(other, [this](const U &el) { this->add(el); });

    return *this;
}

template <CopyMoveAssignable T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    return this->assign(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::assign(Set<U> &&other)
{
    this->clear();

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    other._size = 0;

    return *this;
}

template <CopyMoveAssignable T>
Set<T> &Set<T>::operator=(Set<T> &&other)
{
    return this->assign(std::forward<Set<T>>(other));
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::make_union(const Set<U> &other) const
{
    Set<T> set_union(*this);
    set_union.unite(other);

    return set_union;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::operator|(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::operator+(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::unite(const Set<U> &other)
{
    for (const auto &el : other)
        this->add(el);

    return *this;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator|=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator+=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::make_intersection(const Set<U> &other) const
{
    Set<T> copy;
    for (const auto &el : *this)
        if (other.in(el))
            copy.add(el);

    return copy;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::operator&(const Set<U> &other) const
{
    return this->make_intersection(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::intersect(const Set<U> &other)
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (!other.in(*it))
            this->erase(it);
        else
            ++it;
    }

    return *this;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator&=(const Set<U> &other)
{
    return this->intersect(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::make_difference(const Set<U> &other) const
{
    Set<T> copy(*this);

    for (const auto &el : other)
        copy.erase(el);

    return copy;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::operator-(const Set<U> &other) const
{
    return this->make_difference(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::subtract(const Set<U> &other)
{
    for (const auto &el : other)
        this->erase(el);

    return *this;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator-=(const Set<U> &other)
{
    return this->subtract(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::make_symm_difference(const Set<U> &other) const
{
    Set<T> d1 = *this - other;
    Set<T> d2 = other - *this;
    return d1 + d2;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> Set<T>::operator^(const Set<U> &other) const
{
    return this->make_symm_difference(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::symm_subtract(const Set<U> &other)
{
    Set<T> intersection = *this & other;
    *this += other;
    *this -= intersection;
    return *this;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator^=(const Set<U> &other)
{
    return this->symm_subtract(other);
}

#pragma endregion

#pragma region Compare

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::equal(const Set<U> &other) const
{
    return this->_size == other._size && (*this - other).empty();
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator==(const Set<U> &other) const
{
    return this->equal(other);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::notEqual(const Set<U> &other) const
{
    return !this->equal(other);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator!=(const Set<U> &other) const
{
    return this->notEqual(other);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
std::partial_ordering Set<T>::operator<=>(const Set<U> &other) const
{
    if (this->equal(other))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(other))
        return std::partial_ordering::less;

    if (this->supersetOf(other))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::less(const Set<U> &other) const
{
    return *this < other;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::lessOrEqual(const Set<U> &other) const
{
    return *this <= other;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greater(const Set<U> &other) const
{
    return *this > other;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greaterOrEqual(const Set<U> &other) const
{
    return *this >= other;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::comparable(const Set<U> &other) const
{
    return (*this <=> other) != std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::nonComparable(const Set<U> &other) const
{
    return (*this <=> other) == std::partial_ordering::unordered;
}

#pragma endregion

#pragma region Destructor

template <CopyMoveAssignable T>
Set<T>::~Set()
{
    this->clear();
}

#pragma endregion

#pragma region Output

template <typename T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set)
{
    os << "{";

    for (const auto &el : set)
    {
        os << el;
        if (set.find(el) != set.cend() - 1)
            os << ", ";
    }

    os << "}";
    os << " (" << set.size() << ")";

    return os;
}

#pragma endregion
