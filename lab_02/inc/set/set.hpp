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
    std::ranges::for_each(array, array + size, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T>::Set(std::initializer_list<U> ilist) : Set()
{
    std::ranges::for_each(ilist, [this](const U &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(const Set<T> &other) : Set()
{
    std::ranges::for_each(other, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
Set<T>::Set(Set<T> &&other) noexcept
{
    this->_size = other._size;
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);

    other._size = 0;
}

template <CopyMoveAssignable T>
template <ConvertibleInputIterator<T> It, Sentinel<It> S>
Set<T>::Set(const It &begin, const S &end)
{
    std::ranges::for_each(begin, end, [this](const T &el) { this->add(el); });
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(const C &container)
{
    std::ranges::for_each(container, [this](const T &value) { this->add(value); });
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T>::Set(C &&container)
{
    std::ranges::for_each(container, [this](const T &value) { this->add(std::move(value)); });
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(const R &range)
{
    std::ranges::for_each(range, [this](const T &value) { this->add(value); });
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T>::Set(R &&range)
{
    std::ranges::for_each(range, [this](auto &&value) { this->add(std::move(value)); });
}

#pragma endregion

// Функции и операторы присваивания
#pragma region Assignment

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::assign(const Set<U> &other)
{
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
        newNode = Set<T>::SetNode::create(value);
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
        newNode = Set<T>::SetNode::create(std::move(value));
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
template <EqualityComparableInputIterator<T> It>
bool Set<T>::erase(It &pos) noexcept
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
                temp.reset();
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
template <EqualityComparable<T> U>
bool Set<T>::erase(const U &value) noexcept
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
template <EqualityComparable<T> U>
bool Set<T>::in(const U &value) const noexcept
{
    return this->find(value) != this->cend();
}

template <CopyMoveAssignable T>
template <EqualityComparableInputIterator<T> It>
bool Set<T>::in(const It &it) const noexcept
{
    return this->in(*it);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
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

template <CopyMoveAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_union(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> set_union(*this);
    set_union.unite(container);
    return set_union;
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::unite(const C &container)
{
    std::ranges::for_each(container, [this](const T &el) { this->add(el); });
    return *this;
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_union(const R &range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> set_union(*this);
    set_union.unite(range);
    return set_union;
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::unite(const R &range)
{
    std::ranges::for_each(range, [this](const T &el) { this->add(el); });
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
    std::ranges::for_each(filtered, [&](const auto &el) { copy.add(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::intersect(const Set<U> &other) noexcept
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (!other.in(*it))
            this->erase(it);
        else
            ++it;
    }

    // auto to_erase = other | std::views::filter([&](const T &elem) { return !other.in(elem); });
    // std::ranges::for_each(to_erase, [this](const T &el) { this->erase(el); std::cout << "erasing " << el <<
    // " "; });

    return *this;
}

template <CopyMoveAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_intersection(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> copy;
    auto filtered = *this
                  | std::views::filter([&](const auto &el)
                                       { return std::ranges::find(container, el) != container.cend(); });
    std::ranges::for_each(filtered, [&](const auto &el) { copy.add(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::intersect(const C &container) noexcept
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (std::ranges::find(container, *it) == container.cend())
            this->erase(it);
        else
            ++it;
    }

    return *this;
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_intersection(
    const R &range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> copy;
    auto filtered =
        *this
        | std::views::filter([&](const auto &el) { return std::ranges::find(range, el) != range.cend(); });
    std::ranges::for_each(filtered, [&](const auto &el) { copy.add(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::intersect(const R &range) noexcept
{
    for (auto it = this->cbegin(); it != this->cend();)
    {
        if (std::ranges::find(range, *it) == range.cend())
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
Set<T> &Set<T>::subtract(const Set<U> &other) noexcept
{
    std::ranges::for_each(other, [this](const U &el) { this->erase(el); });

    return *this;
}

template <CopyMoveAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_difference(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> copy(*this);
    std::ranges::for_each(container, [&](const auto &el) { copy.erase(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::subtract(const C &container) noexcept
{
    std::ranges::for_each(container, [this](const auto &el) { this->erase(el); });

    return *this;
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_difference(
    const R &range) const
{
    Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> copy(*this);
    std::ranges::for_each(range, [&](const auto &el) { copy.erase(el); });

    return copy;
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::subtract(const R &range) noexcept
{
    std::ranges::for_each(range, [this](const auto &el) { this->erase(el); });

    return *this;
}

#pragma endregion
#pragma region SymmDifference

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::make_symm_difference(const Set<U> &other) const
{
    return *this + other - (*this & other);
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
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::make_symm_difference(const C &container) const
{
    return *this + container - (*this & container);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::symm_subtract(const C &container)
{
    Set<T> intersection = *this & container;
    *this += container;
    *this -= intersection;
    return *this;
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::make_symm_difference(
    const R &range) const
{
    return *this + range - (*this & range);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::symm_subtract(const R &range)
{
    Set<T> intersection = *this & range;
    *this += range;
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
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator|(const C &container) const
{
    return this->make_union(container);
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator|(const R &range) const
{
    return this->make_union(range);
}

template <CopyMoveAssignable T>
template <HasCommon<T> U>
Set<std::common_type_t<T, U>> Set<T>::operator+(const Set<U> &other) const
{
    return this->make_union(other);
}

template <CopyMoveAssignable T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator+(const C &container) const
{
    return this->make_union(container);
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator+(const R &range) const
{
    return this->make_union(range);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator|=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator|=(const C &container)
{
    return this->unite(container);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator|=(const R &range)
{
    return this->unite(range);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator+=(const Set<U> &other)
{
    return this->unite(other);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator+=(const C &container)
{
    return this->unite(container);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator+=(const R &range)
{
    return this->unite(range);
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
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator&(const C &container) const
{
    return this->make_intersection(container);
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator&(const R &range) const
{
    return this->make_intersection(range);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator&=(const Set<U> &other) noexcept
{
    return this->intersect(other);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator&=(const C &container) noexcept
{
    return this->intersect(container);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator&=(const R &range) noexcept
{
    return this->intersect(range);
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
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator-(const C &container) const
{
    return this->make_difference(container);
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator-(const R &range) const
{
    return this->make_difference(range);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator-=(const Set<U> &other) noexcept
{
    return this->subtract(other);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator-=(const C &container) noexcept
{
    return this->subtract(container);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator-=(const R &range) noexcept
{
    return this->subtract(range);
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
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator^(const C &container) const
{
    return this->make_symm_difference(container);
}

template <CopyMoveAssignable T>
template <CommonRange<T> R>
Set<std::common_type_t<T, typename std::ranges::range_value_t<R>>> Set<T>::operator^(const R &range) const
{
    return this->make_symm_difference(range);
}

template <CopyMoveAssignable T>
template <Convertible<T> U>
Set<T> &Set<T>::operator^=(const Set<U> &other)
{
    return this->symm_subtract(other);
}

template <CopyMoveAssignable T>
template <ConvertibleContainer<T> C>
Set<T> &Set<T>::operator^=(const C &container)
{
    return this->symm_subtract(container);
}

template <CopyMoveAssignable T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator^=(const R &range)
{
    return this->symm_subtract(range);
}

#pragma endregion

#pragma endregion

// Операторы сравнения
#pragma region CompareOperators

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
std::partial_ordering Set<T>::operator<=>(const Set<U> &other) const noexcept
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
template <EqualityComparableContainer<T> C>
std::partial_ordering Set<T>::operator<=>(const C &container) const noexcept
{
    if (this->equal(container))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(container))
        return std::partial_ordering::less;

    if (this->supersetOf(container))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
std::partial_ordering Set<T>::operator<=>(const R &range) const noexcept
{
    if (this->equal(range))
        return std::partial_ordering::equivalent;

    if (this->subsetOf(range))
        return std::partial_ordering::less;

    if (this->supersetOf(range))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator==(const Set<U> &other) const noexcept
{
    return this->equal(other);
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::operator==(const C &container) const noexcept
{
    return this->equal(container);
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::operator==(const R &range) const noexcept
{
    return this->equal(range);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::operator!=(const Set<U> &other) const noexcept
{
    return this->notEqual(other);
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::operator!=(const C &container) const noexcept
{
    return this->notEqual(container);
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::operator!=(const R &range) const noexcept
{
    return this->notEqual(range);
}

#pragma endregion

// Функции сравнения
#pragma region CompareFunctions

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::comparable(const Set<U> &other) const noexcept
{
    return (*this <=> other) != std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::comparable(const C &container) const noexcept
{
    return (*this <=> container) != std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::comparable(const R &range) const noexcept
{
    return (*this <=> range) != std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::nonComparable(const Set<U> &other) const noexcept
{
    return (*this <=> other) == std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::nonComparable(const C &container) const noexcept
{
    return (*this <=> container) == std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::nonComparable(const R &range) const noexcept
{
    return (*this <=> range) == std::partial_ordering::unordered;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::subsetOf(const Set<U> &other) const noexcept
{
    return std::ranges::all_of(*this, [&](const auto &el) { return other.in(el); });
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::subsetOf(const C &container) const noexcept
{
    return std::ranges::all_of(*this, [&](const auto &el)
                               { return std::ranges::find(container, el) != container.cend(); });
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::subsetOf(const R &range) const noexcept
{
    return std::ranges::all_of(*this,
                               [&](const auto &el) { return std::ranges::find(range, el) != range.cend(); });
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::supersetOf(const Set<U> &other) const noexcept
{
    return other.subsetOf(*this);
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::supersetOf(const C &container) const noexcept
{
    return std::ranges::all_of(container, [this](const auto &el) { return this->in(el); });
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::supersetOf(const R &range) const noexcept
{
    return std::ranges::all_of(range, [this](const auto &el) { return this->in(el); });
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::equal(const Set<U> &other) const noexcept
{
    if (this->_size != other._size)
        return false;

    return this->subsetOf(other) && other.subsetOf(*this);
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::equal(const C &container) const noexcept
{
    return this->subsetOf(container)
        && std::ranges::all_of(container, [this](const auto &el) { return this->in(el); });
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::equal(const R &range) const noexcept
{
    return this->subsetOf(range)
        && std::ranges::all_of(range, [this](const auto &el) { return this->in(el); });
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::notEqual(const Set<U> &other) const noexcept
{
    return !this->equal(other);
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::notEqual(const C &container) const noexcept
{
    return !this->equal(container);
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::notEqual(const R &range) const noexcept
{
    return !this->equal(range);
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::less(const Set<U> &other) const noexcept
{
    return *this < other;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::less(const C &container) const noexcept
{
    return *this < container;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::less(const R &range) const noexcept
{
    return *this < range;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::lessOrEqual(const Set<U> &other) const noexcept
{
    return *this <= other;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::lessOrEqual(const C &container) const noexcept
{
    return *this <= container;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::lessOrEqual(const R &range) const noexcept
{
    return *this <= range;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greater(const Set<U> &other) const noexcept
{
    return *this > other;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::greater(const C &container) const noexcept
{
    return *this > container;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::greater(const R &range) const noexcept
{
    return *this > range;
}

template <CopyMoveAssignable T>
template <EqualityComparable<T> U>
bool Set<T>::greaterOrEqual(const Set<U> &other) const noexcept
{
    return *this >= other;
}

template <CopyMoveAssignable T>
template <EqualityComparableContainer<T> C>
bool Set<T>::greaterOrEqual(const C &container) const noexcept
{
    return *this >= container;
}

template <CopyMoveAssignable T>
template <EqualityComparableRange<T> R>
bool Set<T>::greaterOrEqual(const R &range) const noexcept
{
    return *this >= range;
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
