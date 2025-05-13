#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../../component/primitive/invisible/camera/default/DefaultCamera.h"
#include "../../ids/ids.h"

#include <functional>
#include <memory>

class CameraFactory
{
public:
    using CreatorMap = std::map<CameraIds, std::function<std::shared_ptr<BaseCamera>()>>;

private:
    const CreatorMap m_map{
        {CameraIds::DefaultCameraId, [](){ return std::make_shared<DefaultCamera>(); }}
    };

public:
    CameraFactory() = default;

    std::shared_ptr<BaseCamera> create(const CameraIds &id);
};
