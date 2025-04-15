#pragma once

#include <memory>
#include <iterator>

#include "base_iterator.h"
#include "set_node.h"

template <typename Type>
class ConstIterator : public BaseIterator<Type>
{

private:
    // ======================= Геттеры ======================
    SetNode<Type> &getCurr() const; 
    // ================= =================== ================

public:
    // ==================== Конструкторы ====================
    ConstIterator();
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

    // ================= Проверка итератора =================
    operator bool() const;

    void checkExpired(int line) const;
    // ================= ================== =================


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

};

#include "const_iterator.hpp"
