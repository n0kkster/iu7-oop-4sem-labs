#pragma once

#include "base_container.h"
#include "concepts.h"
#include "const_iterator.h"
#include "set_node.h"
#include <initializer_list>

#include <compare>
#include <concepts>
#include <memory>

template <CopyMoveAssignable T>
class Set : public BaseContainer
{

public:
#pragma region Aliases
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ConstIterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
#pragma endregion

#pragma region Constructors
    // ==================== Конструкторы ====================
    Set() = default;

    template <Convertible<T> U>
    Set(const size_t size, const U *array); // К-тор на основе некого массива. +

    template <Convertible<T> U>
    Set(std::initializer_list<U> ilist); // К-тор на основе списка инициализации. +

    explicit Set(const Set<T> &other); // К-тор копирования. +
    Set(Set<T> &&other) noexcept;      // К-тор переноса. +

    template <ConvertibleInputIterator<T> It>
    Set(const It &begin, const It &end); // К-тор по двум итераторам +

    template <ConvertibleContainer<T> C>
    Set(const C &container); // Конструктор от контейнера +

    template <ConvertibleRange<T> R>
    Set(const R &range); // Конструктор от диапазона +


    // Добавить конструктор от range и другого convetible container
    // ==================== ============ ====================
#pragma endregion

#pragma region Destructor
    // ===================== Деструктор =====================
    ~Set(); // +
// ===================== Деструктор =====================
#pragma endregion

    // ================== Основные функции ==================

#pragma region Add
    // ======= Добавление элемента в множество =======
    template <Convertible<T> U>
    bool add(const U &value); // +

    template <Convertible<T> U>
    bool add(U &&value); // +
// ======= ================================ =======
#pragma endregion

#pragma region Find
    // ======== Проверка элемента на вхождение ========
    template <Convertible<T> U>
    bool in(const U &value) const noexcept; // +

    template <ConvertibleInputIterator<T> It>
    bool in(const It &it) const noexcept; // +
    // ======== ============================== ========

    // ================ Поиск элемента ================
    template <Convertible<T> U>
    ConstIterator<T> find(const U &value) const noexcept; // +
    // ================ ============== ================
#pragma endregion

#pragma region Misc
    // ======== Получение количества элементов ========
    size_t size() const noexcept override; // +
    // ======== ============================== ========

    // ============== Очистка множества ===============
    void clear() override; // +
    // =============== ================ ===============

    // ========= Проверка множества на пустоту ========
    bool empty() const noexcept override; // +
    // ========= ============================= ========

    template <Convertible<T> U>
    bool subsetOf(const Set<U> &other) const; // +

    template <Convertible<T> U>
    bool supersetOf(const Set<U> &other) const; // +
#pragma endregion

#pragma region Erase
    // ============== Удаление элемента ===============
    template <Convertible<T> U>
    bool erase(const U &value); // +

    template <ConvertibleInputIterator<T> It>
    bool erase(It &pos); // +
    // ============== ================= ===============
#pragma endregion

    // ================== ============== ====================

#pragma region Iterators
    // ===================== Итераторы ======================
    ConstIterator<T> begin() const noexcept;   // +
    ConstIterator<T> end() const noexcept;     // +
    ConstIterator<T> cbegin() const noexcept;  // +
    ConstIterator<T> cend() const noexcept;    // +
    ConstIterator<T> rbegin() const noexcept;  // +
    ConstIterator<T> rend() const noexcept;    // +
    ConstIterator<T> crbegin() const noexcept; // +
    ConstIterator<T> crend() const noexcept;   // +
// ===================== ========= ======================
#pragma endregion

#pragma region Operators
    // ===================== Операторы ======================

    // ======= Присваивание =======
    // Копирующий оператор присваивания
    template <Convertible<T> U>
    Set<T> &assign(const Set<U> &other);    // +
    Set<T> &operator=(const Set<T> &other); // +

    // Перемещающий оператор присваивания
    template <Convertible<T> U>
    Set<T> &assign(Set<U> &&other);    // +
    Set<T> &operator=(Set<T> &&other); // +
    // ======= ============ =======

    // ======= Объединение =======
    template <Convertible<T> U>
    Set<T> make_union(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> operator|(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> operator+(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> &unite(const Set<U> &other); // +

    template <Convertible<T> U>
    Set<T> &operator|=(const Set<U> &other); // +

    template <Convertible<T> U>
    Set<T> &operator+=(const Set<U> &other); // +
    // ======= =========== =======

    // ======= Пересечение =======
    template <Convertible<T> U>
    Set<T> make_intersection(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> operator&(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> &intersect(const Set<U> &other); // +

    template <Convertible<T> U>
    Set<T> &operator&=(const Set<U> &other); // +
    // ======= =========== =======

    // ======= Разность =======
    template <Convertible<T> U>
    Set<T> make_difference(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> operator-(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> &subtract(const Set<U> &other); // +

    template <Convertible<T> U>
    Set<T> &operator-=(const Set<U> &other); // +
    // ======= ======== =======

    // ======= Симметрическая разность =======
    template <Convertible<T> U>
    Set<T> make_symm_difference(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> operator^(const Set<U> &other) const; // +

    template <Convertible<T> U>
    Set<T> &symm_subtract(const Set<U> &other); // +

    template <Convertible<T> U>
    Set<T> &operator^=(const Set<U> &other); // +
    // ======= =========== =======
#pragma endregion

#pragma region Compare
    // ======== Сравнение ========
    template <EqualityComparable<T> U>
    std::partial_ordering operator<=>(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool less(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool lessOrEqual(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool greater(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool greaterOrEqual(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool equal(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool operator==(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool notEqual(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool operator!=(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool comparable(const Set<U> &other) const;

    template <EqualityComparable<T> U>
    bool nonComparable(const Set<U> &other) const;
    // ======== ========= ========
    // ===================== ========= ======================
#pragma endregion

protected:
    bool add(const std::shared_ptr<SetNode<T>> &node); // +

public:
    std::shared_ptr<SetNode<T>> head;
    std::shared_ptr<SetNode<T>> tail;
};

#include "set.hpp"
