#pragma once

#include <memory>

template <typename Type>
class SetNode
{

private:
    Type data;
    std::shared_ptr<SetNode<Type>> next;
    std::shared_ptr<SetNode<Type>> prev;

public:
    // ==================== Конструкторы ====================
    SetNode() = default;
    explicit SetNode(const Type &value);
    explicit SetNode(Type &&value);
    explicit SetNode(const std::shared_ptr<SetNode<Type>> &pnode);
    // ==================== ============ ====================


    // ===================== Деструктор =====================
    ~SetNode() = default;
    // ===================== ========== =====================


    void exclude();


    // ======================= Сеттеры ======================
    void set(const Type &value) noexcept;
    void setNull();

    void setNext(const SetNode<Type> &node);
    void setNext(const std::shared_ptr<SetNode<Type>> &pnode) noexcept;
    void setNextNull() noexcept;

    void setPrev(const SetNode<Type> &node);
    void setPrev(const std::shared_ptr<SetNode<Type>> &pnode) noexcept;
    void setPrevNull() noexcept;
    // ======================= ======= ======================


    // ======================= Геттеры ======================
    const Type &value() const noexcept;

    std::shared_ptr<SetNode<Type>> getNext() const noexcept;
    std::shared_ptr<SetNode<Type>> getPrev() const noexcept;
    // ======================= ======= ======================

    // ===================== Операторы ======================
    // Мб добавить spaceship

    bool operator==(const std::shared_ptr<SetNode<Type>> &other) const noexcept;
    bool operator!=(const std::shared_ptr<SetNode<Type>> &other) const noexcept;
    bool operator<(const std::shared_ptr<SetNode<Type>> &other) const noexcept;
    bool operator>(const std::shared_ptr<SetNode<Type>> &other) const noexcept;
    // ===================== ========= ======================

};

#include "set_node.hpp"

