#include "ManagerSolution.h"

std::shared_ptr<TransformManager> ManagerSolution::getTransformManager()
{
    return TransformManagerCreator().getInstance();
}

std::shared_ptr<SceneManager> ManagerSolution::getSceneManager()
{
    return SceneManagerCreator().getInstance();
}

std::shared_ptr<DrawManager> ManagerSolution::getDrawManager()
{
    return DrawManagerCreator().getInstance();
}

std::shared_ptr<LoadManager> ManagerSolution::getLoadManager()
{
    return LoadManagerCreator().getInstance();
}
