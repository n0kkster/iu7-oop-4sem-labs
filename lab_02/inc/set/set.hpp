#pragma once

#include "exception.h"
#include "set.h"

#include <concepts>
#include <iostream>

#pragma region Constructors

template <typename Type>
Set<Type>::Set(const size_t size, const Type *array) : Set()
{
    std::cout << "arr cctor called\n";
    for (size_t i = 0; i < size; ++i)
        this->add(array[i]);
}

template <typename Type>
Set<Type>::Set(const std::initializer_list<Type> ilist) : Set()
{
    std::cout << "ilist cctor called\n";
    for (const Type &el : ilist)
        this->add(el);
}

template <typename Type>
Set<Type>::Set(const Set<Type> &other) : Set()
{
    std::cout << "copy cctor called\n";
    for (const auto &el : other)
        this->add(el);
}

template <typename Type>
Set<Type>::Set(Set<Type> &&other) noexcept
{
    std::cout << "move cctor called\n";

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);
}

template <typename Type>
Set<Type>::Set(const ConstIterator<Type> &begin, const ConstIterator<Type> &end)
{
    std::cout << "iter cctor called\n";
    for (auto it = begin; it != end; ++it)
        this->add(*it);
}

#pragma endregion

#pragma region Add

template <typename Type>
bool Set<Type>::add(const std::shared_ptr<SetNode<Type>> &node)
{
    if (this->in(node->value()))
        return false;

    if (this->isEmpty())
    {
        std::shared_ptr<SetNode<Type>> after_last, before_first;
        try
        {
            after_last = std::make_shared<SetNode<Type>>(std::move(SetNode<Type>()));
            before_first = std::make_shared<SetNode<Type>>(std::move(SetNode<Type>()));
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

#pragma endregion

#pragma region Erase

template <typename Type>
bool Set<Type>::erase(ConstIterator<Type> &pos)
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

template <typename Type>
bool Set<Type>::erase(const Type &value)
{
    ConstIterator<Type> it = this->find(value);
    if (it == this->cend())
        return false;

    this->erase(it);
    return true;
}

#pragma endregion

#pragma region Iterators

template <typename Type>
ConstIterator<Type> Set<Type>::cbegin() const noexcept
{
    return ConstIterator<Type>(this->head);
}

template <typename Type>
ConstIterator<Type> Set<Type>::cend() const noexcept
{
    return this->tail ? ConstIterator<Type>(this->tail->getNext()) : ConstIterator<Type>();
}

template <typename Type>
ConstIterator<Type> Set<Type>::begin() const noexcept
{
    return this->cbegin();
}

template <typename Type>
ConstIterator<Type> Set<Type>::end() const noexcept
{
    return this->cend();
}

template <typename Type>
ConstIterator<Type> Set<Type>::crbegin() const noexcept
{
    return this->cbegin();
}

template <typename Type>
ConstIterator<Type> Set<Type>::crend() const noexcept
{
    return this->cend();
}

template <typename Type>
ConstIterator<Type> Set<Type>::rbegin() const noexcept
{
    return this->begin();
}

template <typename Type>
ConstIterator<Type> Set<Type>::rend() const noexcept
{
    return this->end();
}

#pragma endregion

#pragma region Misc

template <typename Type>
bool Set<Type>::isEmpty() const noexcept
{
    return this->_size == 0;
}

template <typename Type>
void Set<Type>::clear()
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

template <typename Type>
size_t Set<Type>::size() const noexcept
{
    return this->_size;
}

#pragma endregion

#pragma region Find

template <typename Type>
bool Set<Type>::in(const Type &value) const noexcept
{
    for (const auto &el : *this)
        if (el == value)
            return true;
    return false;
}

template <typename Type>
bool Set<Type>::in(const ConstIterator<Type> &it) const noexcept
{
    for (const auto &el : *this)
        if (el == *it)
            return true;
    return false;
}

template <typename Type>
ConstIterator<Type> Set<Type>::find(const Type &value) const noexcept
{
    for (auto it = this->cbegin(); it != this->cend(); ++it)
        if (*it == value)
            return it;

    return this->cend();
}

#pragma endregion

#pragma region Operators

template <typename Type>
Set<Type> &Set<Type>::assign(const Set<Type> &other)
{
    if (&other == this)
        return *this;

    this->clear();
    for (const auto &el : other)
        add(el);

    return *this;
}

template <typename Type>
Set<Type> &Set<Type>::operator=(const Set<Type> &other)
{
    return this->assign(other);
}

template <typename Type>
Set<Type> &Set<Type>::assign(Set<Type> &&other)
{
    this->clear();

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    return *this;
}

template <typename Type>
Set<Type> &Set<Type>::operator=(Set<Type> &&other)
{
    return this->assign(std::forward<Set<Type>>(other));
}

template <typename Type>
Set<Type> &Set<Type>::assign(const std::initializer_list<Type> ilist)
{
    this->clear();

    for (const Type &el : ilist)
        this->add(el);

    return *this;
}

template <typename Type>
Set<Type> &Set<Type>::operator=(const std::initializer_list<Type> ilist)
{
    return this->assign(ilist);
}

template <typename Type>
Set<Type> Set<Type>::make_union(const Set<Type> &other) const
{
    Set<Type> set_union(*this);
    set_union.unite(other);

    return set_union;
}

template <typename Type>
Set<Type> Set<Type>::operator|(const Set<Type> &other) const
{
    return this->make_union(other);
}

template <typename Type>
Set<Type> Set<Type>::operator+(const Set<Type> &other) const
{
    return this->make_union(other);
}

template <typename Type>
Set<Type> &Set<Type>::unite(const Set<Type> &other)
{
    for (const auto &el : other)
        this->add(el);

    return *this;
}

template <typename Type>
Set<Type> &Set<Type>::operator|=(const Set<Type> &other)
{
    return this->unite(other);
}

template <typename Type>
Set<Type> &Set<Type>::operator+=(const Set<Type> &other)
{
    return this->unite(other);
}

template <typename Type>
Set<Type> Set<Type>::make_union(const std::initializer_list<Type> ilist) const
{
    return make_union(Set<Type>(ilist));
}

template <typename Type>
Set<Type> Set<Type>::operator|(const std::initializer_list<Type> ilist) const
{
    return this->make_union(ilist);
}

template <typename Type>
Set<Type> Set<Type>::operator+(const std::initializer_list<Type> ilist) const
{
    return this->make_union(ilist);
}

template <typename Type>
Set<Type> &Set<Type>::unite(const std::initializer_list<Type> ilist)
{
    return this->unite(Set<Type>(ilist));
}

template <typename Type>
Set<Type> &Set<Type>::operator|=(const std::initializer_list<Type> ilist)
{
    return this->unite(ilist);
}

template <typename Type>
Set<Type> &Set<Type>::operator+=(const std::initializer_list<Type> ilist)
{
    return this->unite(ilist);
}

template <typename Type>
Set<Type> Set<Type>::make_intersection(const Set<Type> &other) const
{
    Set<Type> copy;
    for (const auto &el : *this)
        if (other.in(el))
            copy.add(el);

    return copy;
}

template <typename Type>
Set<Type> Set<Type>::operator&(const Set<Type> &other) const
{
    return this->make_intersection(other);
}

template <typename Type>
Set<Type> &Set<Type>::intersect(const Set<Type> &other)
{
    *this = std::move(this->make_intersection(other));
    return *this;
}

template <typename Type>
Set<Type> &Set<Type>::operator&=(const Set<Type> &other)
{
    return this->intersect(other);
}

template <typename Type>
Set<Type> Set<Type>::make_intersection(const std::initializer_list<Type> ilist) const
{
    return this->make_intersection(Set<Type>(ilist));
}

template <typename Type>
Set<Type> Set<Type>::operator&(const std::initializer_list<Type> ilist) const
{
    return this->make_intersection(ilist);
}

template <typename Type>
Set<Type> &Set<Type>::intersect(const std::initializer_list<Type> ilist)
{
    return this->intersect(Set<Type>(ilist));
}

template <typename Type>
Set<Type> &Set<Type>::operator&=(const std::initializer_list<Type> ilist)
{
    return this->intersect(ilist);
}

#pragma endregion

#pragma region Destructor

template <typename Type>
Set<Type>::~Set()
{
    this->clear();
}

#pragma endregion

#pragma region Output

template <typename Type>
std::ostream &operator<<(std::ostream &os, const Set<Type> &set)
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
