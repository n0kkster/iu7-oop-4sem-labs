#pragma once

#include "creators/ManagerCreator.h"

class ManagerSolution
{
public:
    ManagerSolution() = delete;
    ~ManagerSolution() = delete;
    ManagerSolution(ManagerSolution &) = delete;

    static std::shared_ptr<DrawManager> getDrawManager();
    static std::shared_ptr<LoadManager> getLoadManager();
    static std::shared_ptr<SceneManager> getSceneManager();
    static std::shared_ptr<TransformManager> getTransformManager();
    static std::shared_ptr<CameraManager> getCameraManager();
};
