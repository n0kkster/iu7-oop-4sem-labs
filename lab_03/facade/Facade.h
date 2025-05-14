#pragma once

#include "../commands/BaseCommand.h"
#include <memory>
class Facade
{
private:
    std::shared_ptr<CameraManager> m_cameraManager;
    std::shared_ptr<LoadManager> m_loadManager;
    std::shared_ptr<DrawManager> m_drawManager;
    std::shared_ptr<SceneManager> m_sceneManager;
    std::shared_ptr<TransformManager> m_transformManager;

public:
    Facade();
    ~Facade() = default;

    void execute(std::shared_ptr<BaseCommand> command);
};