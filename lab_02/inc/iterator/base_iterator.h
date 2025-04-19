#pragma once

#include "concepts.h"

#include <memory>

template <CopyMoveAssignable>
class Set;

template <CopyMoveAssignable T>
class BaseIterator
{
public:
    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

protected:
    std::weak_ptr<typename Set<T>::SetNode> curr;
    friend class Set<T>;
};

#include "base_iterator.hpp"
