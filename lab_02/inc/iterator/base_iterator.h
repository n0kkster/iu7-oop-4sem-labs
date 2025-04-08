#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <cstddef>

class BaseIterator
{
public:
    virtual ~BaseIterator() = 0;
    
protected:
    size_t index;
    size_t size;
};

#endif /* BASE_ITERATOR_H */
