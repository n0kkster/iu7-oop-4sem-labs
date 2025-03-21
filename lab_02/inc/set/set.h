#ifndef SET_H
#define SET_H

#include <compare>
#include <initializer_list>

#include "const_iterator.h"
#include "base_container.h"

template <typename Type>
class Set : public BaseContainer
{

public:

    // ==================== Конструкторы ====================
    Set() = default;
    Set(const size_t size, const Type *array); // К-тор на основе некого массива.
    explicit Set(std::initializer_list<Type> ilist); // К-тор на основе списка инициализации.
    explicit Set(const Set<Type> &other); // К-тор копирования.
    Set(const Set<Type> &&other) noexcept; // К-тор переноса.

    template <typename Iter>
    Set(const Iter &begin, const Iter &end); // К-тор по двум итераторам
    // ==================== ============ ====================


    // ===================== Деструктор =====================
    ~Set() override;
    // ===================== Деструктор =====================


    // ================== Основные функции ==================
    
    // ======= Добавление элементов в множество =======
    void add(const Type &value);
    void add(Type &&value);
    void add(const std::initializer_list<Type> ilist);
    void add(const size_t size, const Type *array);
    // ======= ================================ =======

    // ======== Проверка элемента на вхождение ========
    bool in(const Type &value) const;
    // ======== ============================== ========

    // ======== Получение количества элементов ========
    size_t getSize() override const;
    // ======== ============================== ========

    // ============== Очистка множества ===============
    void clear() override;
    // =============== ================ ===============

    // ========= Проверка множества на пустоту ========
    void isEmpty() override const;
    // ========= ============================= ========

    // ============== Удаление элемента ===============
    bool erase(const Type &value);
    void erase(ConstIterator<Type> pos);
    // ============== ================= ===============

    // ================ Поиск элемента ================
    ConstIterator<Type> find(const Type &value);
    // ================ ============== ================

    // ================== ============== ====================


    // ===================== Итераторы ======================
    ConstIterator<Type> begin() const;
    ConstIterator<Type> end() const;
    // ===================== ========= ======================


    // ===================== Операторы ======================

    // ======= Присваивание =======
    Set<Type> &assign(const set<Type> &other);
    Set<Type> operator=(const Set<Type> &other);

    Set<Type> &assign(set<Type> &&other);
    Set<Type> operator=(Set<Type> &&other);

    Set<Type> &assign(const std::initializer_list<Type> ilist);
    Set<Type> operator=(const std::initializer_list<Type> ilist);
    // ======= ============ =======

    // ======= Объединение =======
    Set<Type> unite(const Set<Type> &other) const;
    Set<Type> operator|(const Set<Type> &other) const;
    Set<Type> &operator|=(const Set<Type> &other);
    Set<Type> operator+(const Set<Type> &other) const;
    Set<Type> &operator+=(const Set<Type> &other);

    Set<Type> unite(const std::initializer_list<Type> ilist) const;
    Set<Type> operator|(const std::initializer_list<Type> ilist) const;
    Set<Type> &operator|=(const std::initializer_list<Type> ilist);
    Set<Type> operator+(const std::initializer_list<Type> ilist) const;
    Set<Type> &operator+=(const std::initializer_list<Type> ilist);
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

    // bool less(Set<Type> &other) const;
    // bool operator<(const Set<Type> &other) const;

    // bool lessOrEqual(Set<Type> &other) const;
    // bool operator<=(const Set<Type> &other) const;

    // bool less(const std::initializer_list<Type> ilist) const;
    // bool operator<(const std::initializer_list<Type> ilist) const;

    // bool lessOrEqual(const std::initializer_list<Type> ilist) const;
    // bool operator<=(const std::initializer_list<Type> ilist) const;

    // bool greater(Set<Type> &other) const;
    // bool operator>(const Set<Type> &other) const;

    // bool greaterOrEqual(Set<Type> &other) const;
    // bool operator>=(const Set<Type> &other) const;

    // bool greater(const std::initializer_list<Type> ilist) const;
    // bool operator>(const std::initializer_list<Type> ilist) const;

    // bool greaterOrEqual(const std::initializer_list<Type> ilist) const;
    // bool operator>=(const std::initializer_list<Type> ilist) const;

    // bool equal(Set<Type> &other) const;
    // bool operator==(const Set<Type> &other) const;

    // bool equal(const std::initializer_list<Type> ilist) const;
    // bool operator==(const std::initializer_list<Type> ilist) const;
    
    // bool notequal(Set<Type> &other) const;
    // bool operator!=(const Set<Type> &other) const;

    // bool notEqual(const std::initializer_list<Type> ilist) const;
    // bool operator!=(const std::initializer_list<Type> ilist) const;
    // ======== ========= ========

    // ===================== ========= ======================

private:

};

#include "set.hpp"

#endif /* SET_H */
