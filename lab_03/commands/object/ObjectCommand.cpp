#include "ObjectCommand.h"

AddObjectCommand::AddObjectCommand(std::shared_ptr<BaseObject> obj) :
    m_action(&SceneManager::addObject), m_object(obj)
{ }

void AddObjectCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_object);
}

RemoveObjectCommand::RemoveObjectCommand(size_t objId) :
    m_action(&SceneManager::removeObject), m_objectid(objId)
{ }

void RemoveObjectCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_objectid);
}

ScaleObjectCommand::ScaleObjectCommand(size_t objId, const ScaleParams &params) :
    m_action(&TransformManager::scaleObject), m_params(params), m_objectId(objId)
{ }

void ScaleObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

MoveObjectCommand::MoveObjectCommand(size_t objId, const MoveParams &params) :
    m_action(&TransformManager::moveObject), m_params(params), m_objectId(objId)
{ }

void MoveObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

RotateObjectCommand::RotateObjectCommand(size_t objId, const RotationParams &params) :
    m_action(&TransformManager::rotateObject), m_params(params), m_objectId(objId)
{ }

void RotateObjectCommand::execute()
{
    ((*m_transformManager).*m_action)(m_objectId, m_params);
}

MakeCompositeCommand::MakeCompositeCommand(std::vector<size_t> objectIds) :
    m_action(&SceneManager::compose), m_objectIds(objectIds)
{ }

void MakeCompositeCommand::execute()
{
    ((*m_sceneManager).*m_action)(m_objectIds);
}
