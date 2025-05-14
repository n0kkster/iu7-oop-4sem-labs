#pragma once

#include "../BaseCommand.h"

class SceneCommand : public BaseCommand
{
public:
    SceneCommand() = default;
    virtual ~SceneCommand() = default;
};

class DrawSceneCommand : public SceneCommand
{
private:
    using Action = void (DrawManager::*)();
    Action m_method;

public:
    DrawSceneCommand();
    virtual ~DrawSceneCommand() = default;

    void execute() override;
};
