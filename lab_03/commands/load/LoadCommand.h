#pragma once

#include "../../ids/ids.h"
#include "../BaseCommand.h"

class LoadCommand : public BaseCommand
{
public:
    LoadCommand() = default;
    virtual ~LoadCommand() = default;
};

class CarcassLoadCommand : public LoadCommand
{
private:
    using Action = void (LoadManager::*)(ReaderId, DirectorId, InternalRepresentationId, const std::string &);

    Action m_action;
    InternalRepresentationId m_repr;
    std::string m_filename;

public:
    CarcassLoadCommand(InternalRepresentationId repr, const std::string &filename);
    virtual ~CarcassLoadCommand() override = default;
     
    void execute() override;
};
