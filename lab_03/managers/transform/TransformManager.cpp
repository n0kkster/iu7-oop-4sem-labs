#include "TransformManager.h"
#include "../../visitors/creators/VisitorCreator.h"
#include "../ManagerSolution.h"

void TransformManager::moveObject(size_t id, const MoveParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    auto visitor = MoveVisitorCreator::create(params);
    object->accept(visitor);
}

void TransformManager::scaleObject(size_t id, const ScaleParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    auto visitor = ScaleVisitorCreator::create(params);
    object->accept(visitor);
}

void TransformManager::rotateObject(size_t id, const RotationParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    auto visitor = RotateVisitorCreator::create(params);
    object->accept(visitor);
}