#pragma once

#include "set_node.h"

#include <memory>

template <typename Type>
class BaseIterator
{
public:
    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

protected:
    std::weak_ptr<SetNode<Type>> curr;
};

#include "base_iterator.hpp"
