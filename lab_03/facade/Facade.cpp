#include "Facade.h"

#include "../managers/ManagerSolution.h"

Facade::Facade()
{
    m_cameraManager = ManagerSolution::getCameraManager();
    m_drawManager = ManagerSolution::getDrawManager();
    m_loadManager = ManagerSolution::getLoadManager();
    m_sceneManager = ManagerSolution::getSceneManager();
    m_transformManager = ManagerSolution::getTransformManager();
}

void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    command->setManagers(m_cameraManager, m_drawManager, m_loadManager, m_sceneManager, m_transformManager);
    command->execute();
}
