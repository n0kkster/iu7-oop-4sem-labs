#include "DefaultProjectionStrategyCreator.h"

#include "../defaut/DefaultProjectionStrategy.h"

std::unique_ptr<BaseProjectionStrategy> DefaultProjectionStrategyCreator::create()
{
    return std::make_unique<DefaultProjectionStrategy>();
}
