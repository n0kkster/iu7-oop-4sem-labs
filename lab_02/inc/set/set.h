#pragma once

#include "base_container.h"
#include "concepts.h"
#include "const_iterator.h"
#include <initializer_list>

#include <compare>
#include <concepts>
#include <memory>

template <CopyMoveAssignable T>
class Set : public BaseContainer
{

public:
// Алиасы для концептов
#pragma region Aliases
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ConstIterator<value_type>;
    using const_iterator = ConstIterator<value_type>;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
#pragma endregion

// Конструкторы класса
#pragma region Constructors
    // ==================== Конструкторы ====================
    Set() = default;

    template <Convertible<T> U>
    Set(const size_t size, const U *array); // К-тор на основе некого массива. +

    template <Convertible<T> U>
    Set(std::initializer_list<U> ilist); // К-тор на основе списка инициализации. +

    explicit Set(const Set<T> &other); // К-тор копирования. +
    Set(Set<T> &&other) noexcept;      // К-тор переноса. +

    template <ConvertibleInputIterator<T> It, Sentinel<It> S>
    explicit Set(const It &begin, const S &end); // К-тор по двум итераторам +

    template <ConvertibleContainer<T> C>
    explicit Set(const C &container); // Конструктор от контейнера +

    template <ConvertibleContainer<T> C>
    explicit Set(C &&container); // +

    template <ConvertibleRange<T> R>
    explicit Set(const R &range); // Конструктор от диапазона +

    template <ConvertibleRange<T> R>
    explicit Set(R &&range); // +
    // ==================== ============ ====================
#pragma endregion

// Функции и операторы присваивания
#pragma region Assignment
    // ======= Присваивание =======
    // Копирующий оператор присваивания от множества
    template <Convertible<T> U>
    Set<T> &assign(const Set<U> &other);    // +
    Set<T> &operator=(const Set<T> &other); // +

    // Перемещающий оператор присваивания от множемтва
    template <Convertible<T> U>
    Set<T> &assign(Set<U> &&other) noexcept;    // +
    Set<T> &operator=(Set<T> &&other) noexcept; // +

    // Копирующий оператор присваивания от списка инициализации
    template <Convertible<T> U>
    Set<T> &assign(std::initializer_list<U> ilist);
    template <Convertible<T> U>
    Set<T> &operator=(std::initializer_list<U> ilist);

    // Копирующий оператор присваивания от контейнера
    template <ConvertibleContainer<T> C>
    Set<T> &assign(const C &container); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator=(const C &container); // +

    // Перемещающий оператор присваивания от контейнера
    template <ConvertibleContainer<T> C>
    Set<T> &assign(C &&container); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator=(C &&container); // +

    // Копирующий оператор присваивания от диапазона
    template <ConvertibleRange<T> R>
    Set<T> &assign(const R &range); // +
    template <ConvertibleRange<T> R>
    Set<T> &operator=(const R &range); // +

    // Перемещающий оператор присваивания от диапазона
    template <ConvertibleRange<T> R>
    Set<T> &assign(R &&range); // +
    template <ConvertibleRange<T> R>
    Set<T> &operator=(R &&range); // +
    // ======= ============ =======
#pragma endregion

// Деструктор класса
#pragma region Destructor
    // ===================== Деструктор =====================
    ~Set() override; // +
// ===================== Деструктор =====================
#pragma endregion

// Функции, принимающие один элемент
#pragma region SingleElementFunctions

// Добавление элемента в множества
#pragma region Add

    // ======= Добавление элемента в множество =======
    template <Convertible<T> U>
    bool add(const U &value); // +

    template <Convertible<T> U>
    bool add(U &&value); // +
// ======= ================================ =======
#pragma endregion
// Поиск элемента в множестве
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
// Удаление элемента из множества
#pragma region Erase
    // ============== Удаление элемента ===============
    template <Convertible<T> U>
    bool erase(const U &value); // +

    template <ConvertibleInputIterator<T> It>
    bool erase(It &pos); // +
    // ============== ================= ===============
#pragma endregion

#pragma endregion

// Получение информации о текущем множестве
#pragma region SetInfo
    // ======== Получение количества элементов ========
    size_t size() const noexcept override; // +
    // ======== ============================== ========

    // ========= Проверка множества на пустоту ========
    bool empty() const noexcept override; // +
    // ========= ============================= ========
#pragma endregion

// Очистка множества
#pragma region Clear
    // ============== Очистка множества ===============
    void clear() noexcept override; // +
    // =============== ================ ===============
#pragma endregion

// Функции для получения итераторов
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

// Математические операции с множествами
#pragma region MathFunctions

// Объединение двух множеств
#pragma region Union
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_union(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_union(const C &container) const; // +
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> make_union(const R &range) const; // +

    template <Convertible<T> U>
    Set<T> &unite(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &unite(const C &container); // +
    template <ConvertibleRange<T> R>
    Set<T> &unite(const R &range); // +
#pragma endregion
// Перемечение двух множеств
#pragma region Intersection
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_intersection(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_intersection(const C &container) const; // +
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> make_intersection(const R &range) const; // +

    template <Convertible<T> U>
    Set<T> &intersect(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &intersect(const C &container); // +
    template <ConvertibleRange<T> R>
    Set<T> &intersect(const R &range); // +
#pragma endregion
// Разность двух множеств
#pragma region Difference
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_difference(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_difference(const C &container) const; // +
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> make_difference(const R &range) const; // +

    template <Convertible<T> U>
    Set<T> &subtract(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &subtract(const C &container); // +
    template <ConvertibleRange<T> R>
    Set<T> &subtract(const R &range); // +
#pragma endregion
// Симметрическая разность
#pragma region SymmDifference
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> make_symm_difference(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> make_symm_difference(const C &container) const; // +
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> make_symm_difference(const R &range) const;

    template <Convertible<T> U>
    Set<T> &symm_subtract(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &symm_subtract(const C &container); // +
    template <ConvertibleRange<T> R>
    Set<T> &symm_subtract(const R &range); // +
#pragma endregion

#pragma endregion

// Операторы для математических операций
#pragma region MathOperators

// Операторы объединения. + += | |=
#pragma region Union
    // ======= Объединение =======
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator|(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator|(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> operator|(const R &range) const;

    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator+(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator+(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> operator+(const R &range) const;

    template <Convertible<T> U>
    Set<T> &operator|=(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator|=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator|=(const R &range);

    template <Convertible<T> U>
    Set<T> &operator+=(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator+=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator+=(const R &range);
    // ======= =========== =======
#pragma endregion
// Операторы пересечения. & &=
#pragma region Intersection
    // ======= Пересечение =======
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator&(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator&(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> operator&(const R &range) const;


    template <Convertible<T> U>
    Set<T> &operator&=(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator&=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator&=(const R &range);
    // ======= =========== =======
#pragma endregion
// Операторы разности. - -=
#pragma region Difference
    // ======= Разность =======
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator-(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator-(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> operator-(const R &range) const;

    template <Convertible<T> U>
    Set<T> &operator-=(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator-=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator-=(const R &range);
    // ======= ======== =======
#pragma endregion
// Операторы симметрической разности. ^ ^=
#pragma region SymmDifference
    // ======= Симметрическая разность =======
    template <HasCommon<T> U>
    Set<std::common_type_t<T, U>> operator^(const Set<U> &other) const; // +
    template <CommonContainer<T> C>
    Set<std::common_type_t<T, typename C::value_type>> operator^(const C &container) const;
    template <CommonRange<T> R>
    Set<std::common_type_t<T, typename R::value_type>> operator^(const R &range) const;

    template <Convertible<T> U>
    Set<T> &operator^=(const Set<U> &other); // +
    template <ConvertibleContainer<T> C>
    Set<T> &operator^=(const C &container);
    template <ConvertibleRange<T> R>
    Set<T> &operator^=(const R &range);
    // ======= =========== =======
#pragma endregion

#pragma endregion

// Операторы сравнения
#pragma region CompareOperators
    template <EqualityComparable<T> U>
    std::partial_ordering operator<=>(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool operator==(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool operator!=(const Set<U> &other) const; // +
#pragma endregion

// Функции сравнения
#pragma region CompareFunctions
    // ======== Сравнение ========
    template <Convertible<T> U>
    bool subsetOf(const Set<U> &other) const noexcept; // +

    template <Convertible<T> U>
    bool supersetOf(const Set<U> &other) const noexcept; // +

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
    bool notEqual(const Set<U> &other) const; // +

    template <EqualityComparable<T> U>
    bool comparable(const Set<U> &other) const;

    template <EqualityComparable<T> U>
    bool nonComparable(const Set<U> &other) const;
    // ======== ========= ========
    // ===================== ========= ======================
#pragma endregion

protected:
// Класс ноды
#pragma region SetNode

    class SetNode
    {

    private:
        T data;
        std::shared_ptr<SetNode> next;

    public:
        // ==================== Конструкторы ====================
        SetNode() = delete;
        explicit SetNode(const T &value) noexcept;
        explicit SetNode(T &&value) noexcept;
        explicit SetNode(const std::shared_ptr<SetNode> &pnode) noexcept;
        // ==================== ============ ====================

        // ===================== Деструктор =====================
        ~SetNode() = default;
        // ===================== ========== =====================

        // ======================= Сеттеры ======================
        void set(const T &value) noexcept;
        void setNull() noexcept;

        void setNext(const SetNode &node);
        void setNext(const std::shared_ptr<SetNode> &pnode) noexcept;
        void setNextNull() noexcept;
        // ======================= ======= ======================

        // ======================= Геттеры ======================
        const T &value() const noexcept;

        std::shared_ptr<SetNode> getNext() const noexcept;
        // ======================= ======= ======================

        // ===================== Операторы ======================
        bool operator==(const std::shared_ptr<SetNode> &other) const noexcept;
        bool operator!=(const std::shared_ptr<SetNode> &other) const noexcept;
        // ===================== ========= ======================
    };

#pragma endregion

    bool add(const std::shared_ptr<SetNode> &node); // +

// Друзья друзьяшки
#pragma region Friends
    friend class BaseIterator<T>;
    friend class ConstIterator<T>;
#pragma endregion

private:
    std::shared_ptr<SetNode> head;
    std::shared_ptr<SetNode> tail;
};

#include "set.hpp"
#include "set_node.hpp"
