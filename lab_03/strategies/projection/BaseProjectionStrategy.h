#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/visible/model/BaseModel.h"

#include <memory>
#include <vector>

class BaseProjectionStrategy
{
public:
    BaseProjectionStrategy() = default;
    virtual ~BaseProjectionStrategy() = default;

    virtual void prepare(std::shared_ptr<const BaseModel> model, std::shared_ptr<const BaseCamera> camera) = 0;
    virtual const std::vector<Vertex> getVertices() const = 0;
    virtual const std::vector<Edge> getEdges() const = 0;
};
