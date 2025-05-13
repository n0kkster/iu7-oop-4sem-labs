#include "CameraManager.h"
#include "../ManagerSolution.h"
#include "../../exceptions/managers/camera/CameraManagerException.h"
#include "../../factories/camera/CameraFactory.h"

void CameraManager::setActiveCamera(size_t id)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto cameraObject = sceneManager->getObject(id);
    auto camera = std::dynamic_pointer_cast<BaseCamera>(cameraObject);

    if (!camera)
        throw CameraManagerInvalidIdException("Passed ID does not belong to camera!");

    m_activeCam = camera;
    m_activeCamId = id;
}

std::shared_ptr<BaseCamera> CameraManager::getActiveCamera() const noexcept
{
    return m_activeCam;
}

void CameraManager::addCamera(const CameraIds &id)
{
    CameraFactory factory;
    auto camera = factory.create(id);

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->addObject(camera);
}

void CameraManager::removeCamera(size_t id)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->removeObject(id);
}