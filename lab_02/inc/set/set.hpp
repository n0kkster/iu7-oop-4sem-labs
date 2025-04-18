#pragma once

#include "exception.h"
#include "set.h"

#include <iostream>

#pragma region Constructors

template <typename T>
Set<T>::Set(const size_t size, const T *array) : Set()
{
    // std::cout << "arr cctor called\n";
    for (size_t i = 0; i < size; ++i)
        this->add(array[i]);
}

template <typename T>
Set<T>::Set(std::initializer_list<T> ilist) : Set()
{
    // std::cout << "ilist cctor called\n";
    for (const T &el : ilist)
        this->add(el);
}

template <typename T>
Set<T>::Set(const Set<T> &other) : Set()
{
    // std::cout << "copy cctor called\n";
    for (const auto &el : other)
        this->add(el);
}

template <typename T>
Set<T>::Set(Set<T> &&other) noexcept
{
    // std::cout << "move cctor called\n";

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);
}

template <typename T>
Set<T>::Set(const ConstIterator<T> &begin, const ConstIterator<T> &end)
{
    // std::cout << "iter cctor called\n";
    for (auto it = begin; it != end; ++it)
        this->add(*it);
}

#pragma endregion

#pragma region Add

template <typename T>
bool Set<T>::add(const std::shared_ptr<SetNode<T>> &node)
{
    if (this->in(node->value()))
        return false;

    if (this->empty())
    {
        std::shared_ptr<SetNode<T>> after_last, before_first;
        try
        {
            after_last = std::make_shared<SetNode<T>>(std::move(SetNode<T>()));
            before_first = std::make_shared<SetNode<T>>(std::move(SetNode<T>()));
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

template <typename T>
template <typename R>
    requires std::same_as<std::decay_t<R>, T>
bool Set<T>::add(R &&value)
{
    if (this->in(value))
        return false;

    std::shared_ptr<SetNode<T>> newNode;
    try
    {
        newNode = std::make_shared<SetNode<T>>(std::forward<R>(value));
    }
    catch (const std::bad_alloc &ex)
    {
        throw MemoryException("Error allocating new node!");
    }

    return add(newNode);
}

#pragma endregion

#pragma region Erase

template <typename T>
bool Set<T>::erase(ConstIterator<T> &pos)
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

template <typename T>
bool Set<T>::erase(const T &value)
{
    ConstIterator<T> it = this->find(value);
    if (it == this->cend())
        return false;

    this->erase(it);
    return true;
}

#pragma endregion

#pragma region Iterators

template <typename T>
ConstIterator<T> Set<T>::cbegin() const noexcept
{
    return ConstIterator<T>(this->head);
}

template <typename T>
ConstIterator<T> Set<T>::cend() const noexcept
{
    return this->tail ? ConstIterator<T>(this->tail->getNext()) : ConstIterator<T>();
}

template <typename T>
ConstIterator<T> Set<T>::begin() const noexcept
{
    return this->cbegin();
}

template <typename T>
ConstIterator<T> Set<T>::end() const noexcept
{
    return this->cend();
}

template <typename T>
ConstIterator<T> Set<T>::crbegin() const noexcept
{
    return this->cbegin();
}

template <typename T>
ConstIterator<T> Set<T>::crend() const noexcept
{
    return this->cend();
}

template <typename T>
ConstIterator<T> Set<T>::rbegin() const noexcept
{
    return this->begin();
}

template <typename T>
ConstIterator<T> Set<T>::rend() const noexcept
{
    return this->end();
}

#pragma endregion

#pragma region Misc

template <typename T>
bool Set<T>::empty() const noexcept
{
    return this->_size == 0;
}

template <typename T>
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

template <typename T>
size_t Set<T>::size() const noexcept
{
    return this->_size;
}

template <typename T>
bool Set<T>::subsetOf(const Set<T> &other) const
{
    for (const auto &el : *this)
        if (!other.in(el))
            return false;

    return true;
}

template <typename T>
bool Set<T>::supersetOf(const Set<T> &other) const
{
    return other.subsetOf(*this);
}

#pragma endregion

#pragma region Find

template <typename T>
bool Set<T>::in(const T &value) const noexcept
{
    for (const auto &el : *this)
        if (el == value)
            return true;
    return false;
}

template <typename T>
bool Set<T>::in(const ConstIterator<T> &it) const noexcept
{
    for (const auto &el : *this)
        if (el == *it)
            return true;
    return false;
}

template <typename T>
ConstIterator<T> Set<T>::find(const T &value) const noexcept
{
    for (auto it = this->cbegin(); it != this->cend(); ++it)
        if (*it == value)
            return it;

    return this->cend();
}

#pragma endregion

#pragma region Operators

template <typename T>
Set<T> &Set<T>::assign(const Set<T> &other)
{
    if (&other == this)
        return *this;

    this->clear();
    for (const auto &el : other)
        add(el);

    return *this;
}

template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    return this->assign(other);
}

template <typename T>
Set<T> &Set<T>::assign(Set<T> &&other)
{
    this->clear();

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    return *this;
}

template <typename T>
Set<T> &Set<T>::operator=(Set<T> &&other)
{
    return this->assign(std::forward<Set<T>>(other));
}

template <typename T>
Set<T> Set<T>::make_union(const Set<T> &other) const
{
    Set<T> set_union(*this);
    set_union.unite(other);

    return set_union;
}

template <typename T>
Set<T> Set<T>::operator|(const Set<T> &other) const
{
    return this->make_union(other);
}

template <typename T>
Set<T> Set<T>::operator+(const Set<T> &other) const
{
    return this->make_union(other);
}

template <typename T>
Set<T> &Set<T>::unite(const Set<T> &other)
{
    for (const auto &el : other)
        this->add(el);

    return *this;
}

template <typename T>
Set<T> &Set<T>::operator|=(const Set<T> &other)
{
    return this->unite(other);
}

template <typename T>
Set<T> &Set<T>::operator+=(const Set<T> &other)
{
    return this->unite(other);
}

template <typename T>
Set<T> Set<T>::make_intersection(const Set<T> &other) const
{
    Set<T> copy;
    for (const auto &el : *this)
        if (other.in(el))
            copy.add(el);

    return copy;
}

template <typename T>
Set<T> Set<T>::operator&(const Set<T> &other) const
{
    return this->make_intersection(other);
}

template <typename T>
Set<T> &Set<T>::intersect(const Set<T> &other)
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

template <typename T>
Set<T> &Set<T>::operator&=(const Set<T> &other)
{
    return this->intersect(other);
}

template <typename T>
Set<T> Set<T>::make_difference(const Set<T> &other) const
{
    Set<T> copy(*this);

    for (const auto &el : other)
        copy.erase(el);

    return copy;
}

template <typename T>
Set<T> Set<T>::operator-(const Set<T> &other) const
{
    return this->make_difference(other);
}

template <typename T>
Set<T> &Set<T>::subtract(const Set<T> &other)
{
    for (const auto &el : other)
        this->erase(el);

    return *this;
}

template <typename T>
Set<T> &Set<T>::operator-=(const Set<T> &other)
{
    return this->subtract(other);
}

template <typename T>
Set<T> Set<T>::make_symm_difference(const Set<T> &other) const
{
    Set<T> d1 = *this - other;
    Set<T> d2 = other - *this;
    return d1 + d2;
}

template <typename T>
Set<T> Set<T>::operator^(const Set<T> &other) const
{
    return this->make_symm_difference(other);
}

template <typename T>
Set<T> &Set<T>::symm_subtract(const Set<T> &other)
{
    Set<T> intersection = *this & other;
    *this += other;
    *this -= intersection;
    return *this;
}

template <typename T>
Set<T> &Set<T>::operator^=(const Set<T> &other)
{
    return this->symm_subtract(other);
}

#pragma endregion

#pragma region Compare

template <typename T>
bool Set<T>::equal(const Set<T> &other) const
{
    return this->_size == other._size && (*this - other).empty();
}

template <typename T>
bool Set<T>::operator==(const Set<T> &other) const
{
    return this->equal(other);
}

template <typename T>
bool Set<T>::notEqual(const Set<T> &other) const
{
    return !this->equal(other);
}

template <typename T>
bool Set<T>::operator!=(const Set<T> &other) const
{
    return this->notEqual(other);
}

template <typename T>
std::partial_ordering Set<T>::operator<=>(const Set<T> &other) const
{
    if (this->equal(other))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(other))
        return std::partial_ordering::less;

    if (this->supersetOf(other))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <typename T>
bool Set<T>::less(const Set<T> &other) const
{
    return *this < other;
}

template <typename T>
bool Set<T>::lessOrEqual(const Set<T> &other) const
{
    return *this <= other;
}

template <typename T>
bool Set<T>::greater(const Set<T> &other) const
{
    return *this > other;
}

template <typename T>
bool Set<T>::greaterOrEqual(const Set<T> &other) const
{
    return *this >= other;
}

template <typename T>
bool Set<T>::comparable(const Set<T> &other) const
{
    return (*this <=> other) != std::partial_ordering::unordered;
}

template <typename T>
bool Set<T>::nonComparable(const Set<T> &other) const
{
    return (*this <=> other) == std::partial_ordering::unordered;
}


#pragma endregion

#pragma region Destructor

template <typename T>
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
