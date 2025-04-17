#pragma once

#include "base_iterator.h"
#include "set_node.h"

#include <iterator>
#include <memory>

template <typename Type>
class ConstIterator : public BaseIterator<Type>
{

private:
    // ======================= Геттеры ======================
    SetNode<Type> &getCurr() const;
    // ================= =================== ================

public:
    // ==================== Конструкторы ====================
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<SetNode<Type>> &pnode);
    ConstIterator(const ConstIterator<Type> &iter);
    // ==================== ============ ====================

    // ===================== Деструктор =====================
    ~ConstIterator() override = default;
    // ===================== ========== =====================

    // ================= Изменение итератора ================
    void next();
    void prev();
    // ================= =================== ================

    // =============== Удаление ноды итератора ==============
    void erase();
    // =============== ======================= ==============

    // ================= Проверка итератора =================
    operator bool() const;

    void checkExpired(int line) const;
    // ================= ================== =================

#pragma region Operators
    // ===================== Операторы ======================
    bool operator==(const ConstIterator<Type> &other) const;
    bool operator!=(const ConstIterator<Type> &other) const;

    ConstIterator<Type> &operator=(const ConstIterator<Type> &other);
    ConstIterator<Type> &operator=(const ConstIterator<Type> &&other);

    const Type &operator*() const;
    const Type *operator->() const;
    const Type &operator[](size_t offset) const;

    ConstIterator<Type> &operator+=(int n);
    ConstIterator<Type> operator+(int n) const;
    ConstIterator<Type> &operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type> &operator-=(int n);
    ConstIterator<Type> operator-(int n) const;
    ConstIterator<Type> &operator--();
    ConstIterator<Type> operator--(int);
    // ===================== ========= ======================
#pragma endregion

};

#include "const_iterator.hpp"
