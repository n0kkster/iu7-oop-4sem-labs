#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include "../BaseManager.h"
#include "../../ids/ids.h"

#include <cstddef>
#include <memory>

class CameraManager : public BaseManager
{
private:
    std::shared_ptr<BaseCamera> m_activeCam;
    size_t m_activeCamId;

public:
    CameraManager() = default;
    virtual ~CameraManager() override = default;

    void setActiveCamera(size_t id);
    std::shared_ptr<BaseCamera> getActiveCamera() const noexcept;

    void addCamera(const CameraIds &id);
    void removeCamera(size_t id);
};
