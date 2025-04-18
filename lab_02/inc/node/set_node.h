#pragma once

#include <memory>

template <typename T>
class SetNode
{

private:
    T data;
    std::shared_ptr<SetNode<T>> next;
    std::shared_ptr<SetNode<T>> prev;

public:
    // ==================== Конструкторы ====================
    SetNode() = default;
    explicit SetNode(const T &value);
    explicit SetNode(T &&value);
    explicit SetNode(const std::shared_ptr<SetNode<T>> &pnode);
    // ==================== ============ ====================


    // ===================== Деструктор =====================
    ~SetNode() = default;
    // ===================== ========== =====================


    void exclude();


    // ======================= Сеттеры ======================
    void set(const T &value) noexcept;
    void setNull();

    void setNext(const SetNode<T> &node);
    void setNext(const std::shared_ptr<SetNode<T>> &pnode) noexcept;
    void setNextNull() noexcept;

    void setPrev(const SetNode<T> &node);
    void setPrev(const std::shared_ptr<SetNode<T>> &pnode) noexcept;
    void setPrevNull() noexcept;
    // ======================= ======= ======================


    // ======================= Геттеры ======================
    const T &value() const noexcept;

    std::shared_ptr<SetNode<T>> getNext() const noexcept;
    std::shared_ptr<SetNode<T>> getPrev() const noexcept;
    // ======================= ======= ======================

    // ===================== Операторы ======================
    // Мб добавить spaceship

    bool operator==(const std::shared_ptr<SetNode<T>> &other) const noexcept;
    bool operator!=(const std::shared_ptr<SetNode<T>> &other) const noexcept;
    
    // Мб убрать эти сравнения
    bool operator<(const std::shared_ptr<SetNode<T>> &other) const noexcept;
    bool operator>(const std::shared_ptr<SetNode<T>> &other) const noexcept;
    // ===================== ========= ======================

};

#include "set_node.hpp"

