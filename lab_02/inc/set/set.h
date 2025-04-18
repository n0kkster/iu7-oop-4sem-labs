#pragma once

#include "base_container.h"
#include "const_iterator.h"
#include "set_concepts.h"
#include "set_node.h"
#include <initializer_list>

#include <compare>
#include <concepts>
#include <memory>

template <typename T>
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
    Set(const size_t size, const T *array); // К-тор на основе некого массива. +
    Set(std::initializer_list<T> ilist);    // К-тор на основе списка инициализации. +
    explicit Set(const Set<T> &other);      // К-тор копирования. +
    Set(Set<T> &&other) noexcept;           // К-тор переноса. +

    // template <typename Iter>
    Set(const ConstIterator<T> &begin, const ConstIterator<T> &end); // К-тор по двум итераторам +

    // Добавить конструктор от range
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
    template <typename R>
        requires std::same_as<std::decay_t<R>, T>
    bool add(R &&value); // +
// ======= ================================ =======
#pragma endregion

#pragma region Find
    // ======== Проверка элемента на вхождение ========
    bool in(const T &value) const noexcept;             // +
    bool in(const ConstIterator<T> &it) const noexcept; // +
    // ======== ============================== ========

    // ================ Поиск элемента ================
    ConstIterator<T> find(const T &value) const noexcept; // +
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

    bool subsetOf(const Set<T> &other) const;   // +
    bool supersetOf(const Set<T> &other) const; // +
#pragma endregion

#pragma region Erase
    // ============== Удаление элемента ===============
    bool erase(const T &value);        // +
    bool erase(ConstIterator<T> &pos); // +
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
    Set<T> &assign(const Set<T> &other);    // +
    Set<T> &operator=(const Set<T> &other); // +

    // Перемещающий оператор присваивания
    Set<T> &assign(Set<T> &&other);    // +
    Set<T> &operator=(Set<T> &&other); // +
    // ======= ============ =======

    // ======= Объединение =======
    Set<T> make_union(const Set<T> &other) const; // +
    Set<T> operator|(const Set<T> &other) const;  // +
    Set<T> operator+(const Set<T> &other) const;  // +

    Set<T> &unite(const Set<T> &other);      // +
    Set<T> &operator|=(const Set<T> &other); // +
    Set<T> &operator+=(const Set<T> &other); // +
    // ======= =========== =======

    // ======= Пересечение =======
    Set<T> make_intersection(const Set<T> &other) const; // +
    Set<T> operator&(const Set<T> &other) const;         // +

    Set<T> &intersect(const Set<T> &other);  // +
    Set<T> &operator&=(const Set<T> &other); // +
    // ======= =========== =======

    // ======= Разность =======
    Set<T> make_difference(const Set<T> &other) const; // +
    Set<T> operator-(const Set<T> &other) const;       // +

    Set<T> &subtract(const Set<T> &other);   // +
    Set<T> &operator-=(const Set<T> &other); // +
    // ======= ======== =======

    // ======= Симметрическая разность =======
    Set<T> make_symm_difference(const Set<T> &other) const; // +
    Set<T> operator^(const Set<T> &other) const;            // +

    Set<T> &symm_subtract(const Set<T> &other); // +
    Set<T> &operator^=(const Set<T> &other);    // +
    // ======= =========== =======
#pragma endregion

#pragma region Compare
    // ======== Сравнение ========
    std::partial_ordering operator<=>(const Set<T> &other) const; // +

    bool less(const Set<T> &other) const;           // +
    bool lessOrEqual(const Set<T> &other) const;    // +
    bool greater(const Set<T> &other) const;        // +
    bool greaterOrEqual(const Set<T> &other) const; // +

    bool equal(const Set<T> &other) const;      // +
    bool operator==(const Set<T> &other) const; // +

    bool notEqual(const Set<T> &other) const;   // +
    bool operator!=(const Set<T> &other) const; // +

    bool comparable(const Set<T> &other) const;
    bool nonComparable(const Set<T> &other) const;
    // ======== ========= ========
    // ===================== ========= ======================
#pragma endregion

protected:
    bool add(const std::shared_ptr<SetNode<T>> &node); // +

private:
    std::shared_ptr<SetNode<T>> head;
    std::shared_ptr<SetNode<T>> tail;
};

#include "set.hpp"
