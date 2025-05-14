#include "BaseCommand.h"

void BaseCommand::setManagers(std::shared_ptr<CameraManager> cameraManager,
                              std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager,
                              std::shared_ptr<SceneManager> sceneManager,
                              std::shared_ptr<TransformManager> transformManager)
{
    m_cameraManager = cameraManager;
    m_drawManager = drawManager;
    m_loadManager = loadManager;
    m_sceneManager = sceneManager;
    m_transformManager = transformManager;
}
