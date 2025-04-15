#pragma once

#include <memory>
#include "set_node.h"

template <typename Type>
class BaseIterator
{
public:
    virtual ~BaseIterator() = 0;
    
protected:
    std::weak_ptr<SetNode<Type>> curr;
};
