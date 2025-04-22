#pragma once

#include "exception.h"
#include "set.h"
#include <initializer_list>

#include <algorithm>
#include <iostream>
#include <ranges>

// Конструкторы класса
#pragma region Constructors

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T>::Set(const size_t size, const U *array) : Set()
{
    std::cout << "called cctor from array\n";
    std::ranges::for_each(array, array + size, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T>::Set(std::initializer_list<U> ilist) : Set()
{
    std::cout << "called cctor from ilist\n";
    std::ranges::for_each(ilist, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(const Set<T> &other) : Set()
{
    std::cout << "called cctor from set lref\n";
    std::ranges::for_each(other, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(Set<T> &&other) noexcept
{
    std::cout << "called cctor from set rref\n";
    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    other._size = 0;
}

template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It, Sentinel<It> S>
Set<T>::Set(const It &begin, const S &end)
{
    std::cout << "called cctor from iters\n";
    std::ranges::for_each(begin, end, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(const C &container)
{
    std::cout << "called cctor from container lref\n";
    std::ranges::for_each(container, [this](const T &value) { this->add(value); });
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(C &&container)
{
    std::cout << "called cctor from container rref\n";
    std::ranges::for_each(container, [this](const T &value) { this->add(std::move(value)); });
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(const R &range)
{
    std::cout << "called cctor from range lref\n";
    std::ranges::for_each(range, [this](const T &value) { this->add(value); });
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(R &&range)
{
    std::cout << "called cctor from range rref\n";
    std::ranges::for_each(range, [this](auto &&value) { this->add(std::move(value)); });
}

#pragma endregion

// Функции и операторы присваивания
#pragma region Assignment

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::assign(const Set<U> &other)
{
    std::cout << "assign from set lref\n";

    if (&other == this)
        return *this;

    this->clear();

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
Set<T> &Set<T>::assign(Set<U> &&other) noexcept
{
    std::cout << "assign from set rref\n";

    this->clear();

    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    other._size = 0;

    return *this;
}

template <CopyMoveAssignable T>
Set<T> &Set<T>::operator=(Set<T> &&other) noexcept
{
    return this->assign(std::forward<Set<T>>(other));
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::assign(std::initializer_list<U> ilist)
{
    std::cout << "assign from ilist\n";

    this->clear();
    std::ranges::for_each(ilist, [this](const T &el) { this->add(el); });
    return *this;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator=(std::initializer_list<U> container)
{
    return this->assign(container);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::assign(const C &container)
{
    std::cout << "assign from container lref\n";

    this->clear();
    std::ranges::for_each(container, [this](const T &el) { this->add(el); });
    return *this;
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator=(const C &container)
{
    return this->assign(container);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::assign(C &&container)
{
    std::cout << "assign from container rref\n";
    this->clear();
    std::ranges::for_each(container, [this](const T &el) { this->add(std::move(el)); });
    return *this;
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator=(C &&container)
{
    return this->assign(std::forward<C>(container));
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::assign(const R &range)
{
    std::cout << "assign from range lref\n";

    this->clear();
    std::ranges::for_each(range, [this](const T &el) { this->add(el); });
    return *this;
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator=(const R &range)
{
    return this->assign(range);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::assign(R &&range)
{
    std::cout << "assign from range rref\n";

    this->clear();
    std::ranges::for_each(range, [this](const T &el) { this->add(std::move(el)); });
    return *this;
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator=(R &&range)
{
    return this->assign(std::forward<R>(range));
}

#pragma endregion

// Деструктор класса
#pragma region Destructor

template <CopyMoveAssignable T>
Set<T>::~Set()
{
    this->clear();
}

#pragma endregion

// Функции, принимающие один элемент
#pragma region SingleElementFunctions

#pragma region Add

template <CopyMoveAssignable T>
bool Set<T>::add(const std::shared_ptr<typename Set<T>::SetNode> &node)
{
    if (this->in(node->value()))
        return false;

    if (this->empty())
    {
        this->head = node;
        this->tail = node;
    }
    else
    {
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

    std::shared_ptr<typename Set<T>::SetNode> newNode;
    try
    {
        newNode = std::make_shared<typename Set<T>::SetNode>(value);
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

    std::shared_ptr<typename Set<T>::SetNode> newNode;
    try
    {
        newNode = std::make_shared<typename Set<T>::SetNode>(std::move(value));
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

    auto temp = this->head;

    if (pos == this->cbegin())
    {
        this->head = this->head->getNext();
        temp.reset();
    }
    else
    {
        auto curr_node = pos.curr.lock();
        while (temp && temp->getNext())
        {
            if (temp->getNext() == curr_node)
            {
                temp->setNext(curr_node->getNext());
                break;
            }
            temp = temp->getNext();
        }
    }

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

#pragma endregion

// Получение информации о текущем множестве
#pragma region SetInfo

template <CopyMoveAssignable T>
bool Set<T>::empty() const noexcept
{
    return this->_size == 0;
}

template <CopyMoveAssignable T>
size_t Set<T>::size() const noexcept
{
    return this->_size;
}

#pragma endregion

// Очистка множества
#pragma region Clear

template <CopyMoveAssignable T>
void Set<T>::clear() noexcept
{
    while (this->head)
    {
        auto temp = this->head;
        this->head = this->head->getNext();
        temp->setNextNull();
        temp.reset();
    }

    this->tail.reset();
    this->_size = 0;
}

#pragma endregion

// Функции для получения итераторов
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

// Математические операции с множествами
#pragma region MathFunctions

#pragma region Union

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_union(const Set<U> &other) const
{
    Set<std::common_type_t<T, U>> set_union(*this);
    set_union.unite(other);

    return set_union;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::unite(const Set<U> &other)
{
    std::ranges::for_each(other, [this](const U &el) { this->add(el); });

    return *this;
}

#pragma endregion
#pragma region Intersection

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_intersection(const Set<U> &other) const
{
    Set<std::common_type_t<T, U>> copy;

    auto filtered = *this | std::views::filter([&](const auto &el) { return other.in(el); });
    std::ranges::for_each(filtered, [&](const U &el) { copy.add(el); });

    return copy;
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

#pragma endregion
#pragma region Difference

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_difference(const Set<U> &other) const
{
    Set<std::common_type_t<T, U>> copy(*this);

    std::ranges::for_each(other, [&](const U &el) { copy.erase(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::subtract(const Set<U> &other)
{
    std::ranges::for_each(other, [this](const U &el) { this->erase(el); });

    return *this;
}

#pragma endregion
#pragma region SymmDifference

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_symm_difference(const Set<U> &other) const
{
    Set<std::common_type_t<T, U>> d1 = *this - other;
    Set<std::common_type_t<T, U>> d2 = other - *this;
    return d1 + d2;
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

#pragma endregion

#pragma endregion

// Операторы для математических операций
#pragma region MathOperators

#pragma region Union

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator|(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator+(const Set<U> &other) const
{
    return this->make_union(other);
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

#pragma endregion
#pragma region Intersection

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator&(const Set<U> &other) const
{
    return this->make_intersection(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator&=(const Set<U> &other)
{
    return this->intersect(other);
}

#pragma endregion
#pragma region Difference

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator-(const Set<U> &other) const
{
    return this->make_difference(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator-=(const Set<U> &other)
{
    return this->subtract(other);
}

#pragma endregion
#pragma region SymmDifference

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator^(const Set<U> &other) const
{
    return this->make_symm_difference(other);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator^=(const Set<U> &other)
{
    return this->symm_subtract(other);
}

#pragma endregion

#pragma endregion

// Операторы сравнения
#pragma region CompareOperators

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
bool Set<T>::operator==(const Set<U> &other) const
{
    return this->equal(other);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator!=(const Set<U> &other) const
{
    return this->notEqual(other);
}

#pragma endregion

// Функции сравнения
#pragma region CompareFunctions

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::subsetOf(const Set<U> &other) const noexcept
{
    auto cnt = std::ranges::count_if(*this, [&](const U &el) { return other.in(el); });

    return cnt == _size;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
bool Set<T>::supersetOf(const Set<U> &other) const noexcept
{
    return other.subsetOf(*this);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::equal(const Set<U> &other) const
{
    return this->_size == other._size && (*this - other).empty();
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::notEqual(const Set<U> &other) const
{
    return !this->equal(other);
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

// Вывод множества на экран
#pragma region Output

template <typename T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set)
{
    os << "{";

    std::ranges::for_each(set, [&](const T &el) { os << el << ", "; });

    os << "}";
    os << " (" << set.size() << ")";

    return os;
}

#pragma endregion
