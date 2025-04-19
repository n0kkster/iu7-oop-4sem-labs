#pragma once

#include "base_iterator.h"
#include "concepts.h"

#include <iterator>
#include <memory>

template <CopyMoveAssignable T>
class Set;

template <CopyMoveAssignable T>
class ConstIterator : public BaseIterator<T>
{

public:
#pragma region Aliases
    using pointer = std::shared_ptr<T>;
    using reference = T &;
    using value_type = T;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
#pragma endregion

#pragma region Constructors
    // ==================== Конструкторы ====================
    ConstIterator() noexcept;
    explicit ConstIterator(const std::shared_ptr<typename Set<T>::SetNode> &pnode) noexcept;
    ConstIterator(const ConstIterator<T> &other);
    // ==================== ============ ====================
#pragma endregion

#pragma region Destructor
    // ===================== Деструктор =====================
    ~ConstIterator() override = default;
    // ===================== ========== =====================
#pragma endregion

    // ================= Изменение итератора ================
    void next() noexcept;
    // ================= =================== ================

    // ================= Проверка итератора =================
    operator bool() const noexcept;
    void checkExpired() const;
    // ================= ================== =================

#pragma region Operators
    // ===================== Операторы ======================
    bool operator==(const ConstIterator<T> &other) const noexcept;
    bool operator!=(const ConstIterator<T> &other) const noexcept;

    ConstIterator<T> &operator=(const ConstIterator<T> &other);
    ConstIterator<T> &operator=(ConstIterator<T> &&other);

    const T &operator*() const;
    const std::shared_ptr<T> operator->() const;

    ConstIterator<T> operator+(int n) const noexcept;
    ConstIterator<T> &operator++() noexcept;
    ConstIterator<T> operator++(int) noexcept;
    // ===================== ========= ======================
#pragma endregion

private:
    // ======================= Геттеры ======================
    typename Set<T>::SetNode &getCurr() const noexcept;
    // ================= =================== ================
};

#include "const_iterator.hpp"
