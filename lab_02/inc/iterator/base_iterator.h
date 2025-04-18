#pragma once

#include "set_node.h"

#include <memory>

template <typename T>
class BaseIterator
{
public:
    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

protected:
    std::weak_ptr<SetNode<T>> curr;
};

#include "base_iterator.hpp"
