#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/visible/model/structure/BaseStructure.h"

#include <memory>
#include <vector>

class BaseProjectionStrategy
{
public:
    BaseProjectionStrategy() = default;
    virtual ~BaseProjectionStrategy() = default;

    virtual void project(std::shared_ptr<const BaseStructure> structure,
                         std::shared_ptr<const BaseCamera> camera, std::vector<Vertex> &projected) = 0;
};
