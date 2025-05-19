#pragma once

#include <memory>

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    
    virtual void execute() = 0;
};
