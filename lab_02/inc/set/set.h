#pragma once

#include "base_container.h"
#include "const_iterator.h"
#include "set_node.h"
#include <initializer_list>

#include <compare>
#include <concepts>
#include <memory>

template <typename Type>
class Set : public BaseContainer
{

public:
#pragma region Aliases
    using value_type = Type;
    using reference = Type &;
    using const_reference = const Type &;
    using iterator = ConstIterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    using difference_type = ptrdiff_t;
    using size_type = size_t; 
#pragma endregion

#pragma region Constructors
    // ==================== Конструкторы ====================
    Set() = default;
    Set(const size_t size, const Type *array);       // К-тор на основе некого массива. +
    explicit Set(const std::initializer_list<Type> ilist); // К-тор на основе списка инициализации. +
    explicit Set(const Set<Type> &other);            // К-тор копирования. +
    Set(Set<Type> &&other) noexcept;           // К-тор переноса. +

    // template <typename Iter>
    Set(const ConstIterator<Type> &begin, const ConstIterator<Type> &end); // К-тор по двум итераторам +

    // Добавить конструктор от range
    // ==================== ============ ====================
#pragma endregion

#pragma region Destructor
    // ===================== Деструктор =====================
    ~Set(); // +
// ===================== Деструктор =====================
#pragma endregion

    // ================== Основные функции ==================

#pragma region ElementAddition
    // ======= Добавление элементов в множество =======
    template <typename T>
        requires std::same_as<std::decay_t<T>, Type>
    bool add(T &&value); // +
    // bool add(const std::initializer_list<Type> ilist); // + мб убрать
    // bool add(const size_t size, const Type *array); // + мб убрать
// ======= ================================ =======
#pragma endregion

#pragma region Find
    // ======== Проверка элемента на вхождение ========
    bool in(const Type &value) const noexcept; // +
    bool in(const ConstIterator<Type> &it) const noexcept; // +
    // ======== ============================== ========

    // ================ Поиск элемента ================
    ConstIterator<Type> find(const Type &value) const noexcept; // +
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
    bool isEmpty() const noexcept override; // +
    // ========= ============================= ========
#pragma endregion

    // ============== Удаление элемента ===============
    bool erase(const Type &value);
    void erase(ConstIterator<Type> pos);
    // ============== ================= ===============

    // ================== ============== ====================

#pragma region Iterators
    // ===================== Итераторы ======================
    ConstIterator<Type> begin() const noexcept; // +
    ConstIterator<Type> end() const noexcept; // +
    ConstIterator<Type> cbegin() const noexcept; // +
    ConstIterator<Type> cend() const noexcept; // +
    ConstIterator<Type> rbegin() const noexcept; // +
    ConstIterator<Type> rend() const noexcept; // +
    ConstIterator<Type> crbegin() const noexcept; // +
    ConstIterator<Type> crend() const noexcept; // +
// ===================== ========= ======================
#pragma endregion

#pragma region Operators
    // ===================== Операторы ======================

    // ======= Присваивание =======
    // Копирующий оператор присваивания
    Set<Type> &assign(const Set<Type> &other); // +
    Set<Type> &operator=(const Set<Type> &other); // +

    // Перемещающий оператор присваивания
    Set<Type> &assign(Set<Type> &&other); // +
    Set<Type> &operator=(Set<Type> &&other); // +

    Set<Type> &assign(const std::initializer_list<Type> ilist); // +
    Set<Type> &operator=(const std::initializer_list<Type> ilist); // +
    // ======= ============ =======

    // ======= Объединение =======
    Set<Type> make_union(const Set<Type> &other) const; // +
    Set<Type> operator|(const Set<Type> &other) const; // +
    Set<Type> operator+(const Set<Type> &other) const; // +

    Set<Type> &unite(const Set<Type> &other); // +
    Set<Type> &operator|=(const Set<Type> &other); // +
    Set<Type> &operator+=(const Set<Type> &other); // +

    Set<Type> make_union(const std::initializer_list<Type> ilist) const; // +
    Set<Type> operator|(const std::initializer_list<Type> ilist) const; // +
    Set<Type> operator+(const std::initializer_list<Type> ilist) const; // +

    Set<Type> &unite(const std::initializer_list<Type> ilist); // +
    Set<Type> &operator|=(const std::initializer_list<Type> ilist); // +
    Set<Type> &operator+=(const std::initializer_list<Type> ilist); // +
    // ======= =========== =======

    // ======= Пересечение =======
    Set<Type> intersect(const Set<Type> &other) const;
    Set<Type> operator&(const Set<Type> &other) const;
    Set<Type> &operator&=(const Set<Type> &other);

    Set<Type> intersect(const std::initializer_list<Type> ilist) const;
    Set<Type> operator&(const std::initializer_list<Type> ilist) const;
    Set<Type> &operator&=(const std::initializer_list<Type> ilist);
    // ======= =========== =======

    // ======= Разность =======
    Set<Type> difference(const Set<Type> &other) const;
    Set<Type> operator-(const Set<Type> &other) const;
    Set<Type> &operator-=(const Set<Type> &other);

    Set<Type> difference(const std::initializer_list<Type> ilist) const;
    Set<Type> operator-(const std::initializer_list<Type> ilist) const;
    Set<Type> &operator-=(const std::initializer_list<Type> ilist);
    // ======= =========== =======

    // ======= Симметрическая разность =======
    Set<Type> symmetric_difference(const Set<Type> &other) const;
    Set<Type> operator^(const Set<Type> &other) const;
    Set<Type> &operator^=(const Set<Type> &other);

    Set<Type> symmetric_difference(const std::initializer_list<Type> ilist) const;
    Set<Type> operator^(const std::initializer_list<Type> ilist) const;
    Set<Type> &operator^=(const std::initializer_list<Type> ilist);
    // ======= =========== =======

    // ======== Сравнение ========
    std::partial_ordering operator<=>(const Set<Type> &other) const;
    std::partial_ordering operator<=>(const std::initializer_list<Type> ilist) const;

    bool less(Set<Type> &other) const;
    // bool operator<(const Set<Type> &other) const;

    bool lessOrEqual(Set<Type> &other) const;
    // bool operator<=(const Set<Type> &other) const;

    bool less(const std::initializer_list<Type> ilist) const;
    // bool operator<(const std::initializer_list<Type> ilist) const;

    bool lessOrEqual(const std::initializer_list<Type> ilist) const;
    // bool operator<=(const std::initializer_list<Type> ilist) const;

    bool greater(Set<Type> &other) const;
    // bool operator>(const Set<Type> &other) const;

    bool greaterOrEqual(Set<Type> &other) const;
    // bool operator>=(const Set<Type> &other) const;

    bool greater(const std::initializer_list<Type> ilist) const;
    // bool operator>(const std::initializer_list<Type> ilist) const;

    bool greaterOrEqual(const std::initializer_list<Type> ilist) const;
    // bool operator>=(const std::initializer_list<Type> ilist) const;

    bool equal(Set<Type> &other) const;
    // bool operator==(const Set<Type> &other) const;

    bool equal(const std::initializer_list<Type> ilist) const;
    // bool operator==(const std::initializer_list<Type> ilist) const;

    bool notEqual(Set<Type> &other) const;
    // bool operator!=(const Set<Type> &other) const;

    bool notEqual(const std::initializer_list<Type> ilist) const;
// bool operator!=(const std::initializer_list<Type> ilist) const;
// ======== ========= ========
#pragma endregion

    // ===================== ========= ======================

protected:
    bool add(const std::shared_ptr<SetNode<Type>> &node); // +

private:
    std::shared_ptr<SetNode<Type>> head;
    std::shared_ptr<SetNode<Type>> tail;
};

#include "set.hpp"
