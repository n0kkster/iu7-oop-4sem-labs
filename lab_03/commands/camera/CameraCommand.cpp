#include "CameraCommand.h"

#include "../../managers/ManagerSolution.h"

AddCameraCommand::AddCameraCommand(const CameraId &id) :
    m_action(&CameraManager::addCamera), m_id(id), m_cameraManager(ManagerSolution::getCameraManager())
{ }

void AddCameraCommand::execute()
{
    ((*m_cameraManager).*m_action)(m_id);
}

DeleteCameraCommand::DeleteCameraCommand(const size_t cameraId) :
    m_action(&CameraManager::removeCamera), m_cameraId(cameraId),
    m_cameraManager(ManagerSolution::getCameraManager())
{ }

void DeleteCameraCommand::execute()
{
    ((*m_cameraManager).*m_action)(m_cameraId);
}

SetActiveCameraCommand::SetActiveCameraCommand(size_t cameraId) :
    m_action(&CameraManager::setActiveCamera), m_cameraId(cameraId),
    m_cameraManager(ManagerSolution::getCameraManager())
{ }

void SetActiveCameraCommand::execute()
{
    ((*m_cameraManager).*m_action)(m_cameraId);
}

MoveCameraCommand::MoveCameraCommand(const size_t cameraId, const MoveParams &params) :
    m_action(&TransformManager::moveObject), m_cameraId(cameraId), m_params(params),
    m_transformManager(ManagerSolution::getTransformManager())
{ }

void MoveCameraCommand::execute()
{
    ((*m_transformManager).*m_action)(m_cameraId, m_params);
}

RotateCameraCommand::RotateCameraCommand(const size_t cameraId, const RotationParams &params) :
    m_action(&TransformManager::rotateObject), m_cameraId(cameraId), m_params(params),
    m_transformManager(ManagerSolution::getTransformManager())
{ }

void RotateCameraCommand::execute()
{
    ((*m_transformManager).*m_action)(m_cameraId, m_params);
}
