#pragma once

#include "../commands/BaseCommand.h"

#include <memory>

class Facade
{
public:
    Facade() = default;
    ~Facade() = default;

    void execute(const std::shared_ptr<BaseCommand> &command);
};
