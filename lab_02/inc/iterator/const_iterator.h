#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>
#include <iterator>

#include "set_node.h"

template <typename Type>
class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, Type>
{

private:
    std::weak_ptr<SetNode<Type>> curr;

public:
    // ==================== Конструкторы ====================
    ConstIterator();
    explicit ConstIterator(const std::shared_ptr<SetNode<Type>> &pnode);
    ConstIterator(const ConstIterator<Type> &iter);
    // ==================== ============ ====================

    // ===================== Деструктор =====================
    ~ConstIterator() = default;
    // ===================== ========== =====================

    // ================= Изменение итератора ================
    void next();
    void prev();
    // ================= Изменение итератора ================

    // ================= Проверка итератора =================
    operator bool() const noexcept;
    // ================= ================== =================


    // ===================== Операторы ======================
    std::partial_ordering operator<=>(const ConstIterator<Type> &other);

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

#endif /* CONST_ITERATOR_H */
