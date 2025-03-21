#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <iterator>

template <typename Type>
class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, Type>
{
    
};

#endif /* CONST_ITERATOR_H */
