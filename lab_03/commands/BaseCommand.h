#pragma once

#include "../managers/camera/CameraManager.h"
#include "../managers/draw/DrawManager.h"
#include "../managers/load/LoadManager.h"
#include "../managers/scene/SceneManager.h"
#include "../managers/transform/TransformManager.h"

#include <memory>

class BaseCommand
{
protected:
    std::shared_ptr<CameraManager> m_cameraManager;
    std::shared_ptr<DrawManager> m_drawManager;
    std::shared_ptr<LoadManager> m_loadManager;
    std::shared_ptr<SceneManager> m_sceneManager;
    std::shared_ptr<TransformManager> m_transformManager;

public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    void setManagers(std::shared_ptr<CameraManager> cameraManager, std::shared_ptr<DrawManager> drawManager,
                     std::shared_ptr<LoadManager> loadManager, std::shared_ptr<SceneManager> sceneManager,
                     std::shared_ptr<TransformManager> transformManager);

    virtual void execute() = 0;
};
