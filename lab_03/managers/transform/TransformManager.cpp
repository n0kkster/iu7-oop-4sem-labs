#include "TransformManager.h"
#include "../../visitors/creators/ConcreteVisitorCreator.h"
#include "../ManagerSolution.h"

void TransformManager::moveObject(size_t id, const MoveParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    MoveVisitorCreator creator;
    auto visitor = creator.create(params);
    object->accept(visitor);
}

void TransformManager::scaleObject(size_t id, const ScaleParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    ScaleVisitorCreator creator;
    auto visitor = creator.create(params);
    object->accept(visitor);
}

void TransformManager::rotateObject(size_t id, const RotationParams &params)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto object = sceneManager->getObject(id);

    RotateVisitorCreator creator;
    auto visitor = creator.create(params);
    object->accept(visitor);
}