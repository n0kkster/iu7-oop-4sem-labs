#pragma once

#include "../BaseProjectionStrategy.h"

#include <memory>

class DefaultProjectionStrategyCreator
{
public:
    DefaultProjectionStrategyCreator() = default;
    ~DefaultProjectionStrategyCreator() = default;
    
    std::unique_ptr<BaseProjectionStrategy> create();
};
