#include "ObjectCommand.h"

#include "../../managers/ManagerSolution.h"

AddObjectCommand::AddObjectCommand(std::shared_ptr<BaseObject> obj) :
    m_action(&SceneManager::addObject), m_object(obj), m_sceneManager(ManagerSolution::getSceneManager())
{ }

void AddObjectCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_object);
}

RemoveObjectCommand::RemoveObjectCommand(size_t objId) :
    m_action(&SceneManager::removeObject), m_objectid(objId),
    m_sceneManager(ManagerSolution::getSceneManager())
{ }

void RemoveObjectCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_objectid);
}

ScaleObjectCommand::ScaleObjectCommand(size_t objId, const ScaleParams &params) :
    m_action(&TransformManager::scaleObject), m_params(params), m_objectId(objId),
    m_transformManager(ManagerSolution::getTransformManager())
{ }

void ScaleObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

MoveObjectCommand::MoveObjectCommand(size_t objId, const MoveParams &params) :
    m_action(&TransformManager::moveObject), m_params(params), m_objectId(objId),
    m_transformManager(ManagerSolution::getTransformManager())
{ }

void MoveObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

RotateObjectCommand::RotateObjectCommand(size_t objId, const RotationParams &params) :
    m_action(&TransformManager::rotateObject), m_params(params), m_objectId(objId),
    m_transformManager(ManagerSolution::getTransformManager())
{ }

void RotateObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

ComposeCommand::ComposeCommand(std::vector<size_t> objectIds) :
    m_action(&SceneManager::compose), m_objectIds(objectIds),
    m_sceneManager(ManagerSolution::getSceneManager())
{ }

void ComposeCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_objectIds);
}

GetObjectCenterCommand::GetObjectCenterCommand(size_t id, Vertex &center) :
    m_action(&SceneManager::getCenter), m_id(id), m_center(center),
    m_sceneManager(ManagerSolution::getSceneManager())
{ }

void GetObjectCenterCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_id, m_center);
}
