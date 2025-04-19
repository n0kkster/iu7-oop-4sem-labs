#pragma once

#include "base_iterator.h"

template <CopyMoveAssignable T>
BaseIterator<T>::~BaseIterator() { }
