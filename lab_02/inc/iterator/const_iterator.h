#pragma once

#include "base_iterator.h"
#include "set_node.h"
#include "concepts.h"

#include <iterator>
#include <memory>

template <CopyMoveAssignable T>
class ConstIterator : public BaseIterator<T>
{

public:
#pragma region Aliases
    using pointer = std::shared_ptr<T>;
    using reference = T &;
    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
#pragma endregion

#pragma region Constructors
    // ==================== Конструкторы ====================
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<SetNode<T>> &pnode);
    ConstIterator(const ConstIterator<T> &iter);
    // ==================== ============ ====================
#pragma endregion

#pragma region Destructor
    // ===================== Деструктор =====================
    ~ConstIterator() override = default;
    // ===================== ========== =====================
#pragma endregion

    // ================= Изменение итератора ================
    void next();
    void prev();
    // ================= =================== ================

    // ============== Удаление ноды по итератору ============
    void erase() const;
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
    ConstIterator<T> &operator=(ConstIterator<T> &&other);

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

private:
    // ======================= Геттеры ======================
    SetNode<T> &getCurr() const;
    // ================= =================== ================

};

#include "const_iterator.hpp"
