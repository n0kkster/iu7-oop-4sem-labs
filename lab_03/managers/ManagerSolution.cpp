#include "ManagerSolution.h"

#include <iostream>

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
    auto inst = DrawManagerCreator().getInstance();
    std::cout << "getDrawManager(): drawManager instance: " << inst << std::endl;
    return inst;
}

std::shared_ptr<LoadManager> ManagerSolution::getLoadManager()
{
    return LoadManagerCreator().getInstance();
}

std::shared_ptr<CameraManager> ManagerSolution::getCameraManager()
{
    return CameraManagerCreator().getInstance();
}
