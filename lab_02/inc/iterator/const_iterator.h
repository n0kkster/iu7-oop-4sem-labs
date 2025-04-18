#pragma once

#include "base_iterator.h"
#include "set_node.h"

#include <iterator>
#include <memory>

template <typename T>
class ConstIterator : public BaseIterator<T>
{

private:
    // ======================= Геттеры ======================
    SetNode<T> &getCurr() const;
    // ================= =================== ================

public:
    // ==================== Конструкторы ====================
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<SetNode<T>> &pnode);
    ConstIterator(const ConstIterator<T> &iter);
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
    bool operator==(const ConstIterator<T> &other) const;
    bool operator!=(const ConstIterator<T> &other) const;

    ConstIterator<T> &operator=(const ConstIterator<T> &other);
    ConstIterator<T> &operator=(const ConstIterator<T> &&other);

    const T &operator*() const;
    const T *operator->() const;
    const T &operator[](size_t offset) const;

    ConstIterator<T> &operator+=(int n);
    ConstIterator<T> operator+(int n) const;
    ConstIterator<T> &operator++();
    ConstIterator<T> operator++(int);

    ConstIterator<T> &operator-=(int n);
    ConstIterator<T> operator-(int n) const;
    ConstIterator<T> &operator--();
    ConstIterator<T> operator--(int);
    // ===================== ========= ======================
#pragma endregion

};

#include "const_iterator.hpp"
