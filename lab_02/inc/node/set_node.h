#ifndef SET_NODE_H
#define SET_NODE_H

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
    explicit SetNode(const Type value);
    explicit SetNode(std::shared_ptr<SetNode<Type>> &node);
    // ==================== ============ ====================


    // ===================== Деструктор =====================
    ~SetNode() = default;
    // ===================== Деструктор =====================


    void exclude();


    // ======================= Сеттеры ======================
    void set(const Type &value);
    void setNull();

    void setNext(const SetNode<Type> &node);
    void setNext(const std::shared_ptr<SetNode<Type>> &pnode);
    void setNextNull();

    void setPrev(const SetNode<Type> &node);
    void setPrev(const std::shared_ptr<SetNode<Type>> &pnode);
    void setPrevNull();
    // ======================= ======= ======================


    // ======================= Геттеры ======================
    const Type &getData() const;

    std::shared_ptr<SetNode<Type>> getNext() const;
    std::shared_ptr<SetNode<Type>> getPrev() const;
    // ======================= ======= ======================

    // ===================== Операторы ======================
    bool operator==(const std::shared_ptr<SetNode<Type>> &other) const;
    bool operator!=(const std::shared_ptr<SetNode<Type>> &other) const;
    bool operator<(const std::shared_ptr<SetNode<Type>> &other) const;
    bool operator>(const std::shared_ptr<SetNode<Type>> &other) const;
    // ===================== ========= ======================

};

#include "set_node.hpp"

#endif /* SET_NODE_H */
