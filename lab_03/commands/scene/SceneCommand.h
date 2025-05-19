#pragma once

#include "../../managers/draw/DrawManager.h"
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

    std::shared_ptr<DrawManager> m_drawManager;

public:
    DrawSceneCommand();
    virtual ~DrawSceneCommand() = default;

    void execute() override;
};
