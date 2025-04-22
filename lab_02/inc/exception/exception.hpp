#pragma once

#include "exception.h"

IteratorException::IteratorException(const char *info, const std::source_location &loc) :
    BaseException(info, loc) { };

SetException::SetException(const char *info, const std::source_location &loc) : 
    BaseException(info, loc) { };

MemoryException::MemoryException(const char *info, const std::source_location &loc) :
    SetException(info, loc) { };
    