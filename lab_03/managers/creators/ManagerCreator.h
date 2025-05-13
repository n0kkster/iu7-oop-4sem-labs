#pragma once

#include "../../concepts/concepts.h"
#include "../BaseManager.h"
#include "../draw/DrawManager.h"
#include "../load/LoadManager.h"
#include "../scene/SceneManager.h"
#include "../transform/TransformManager.h"

#include <memory>

template <typename BaseManager, typename DerivedManager, typename... Args>
    requires(std::is_base_of_v<BaseManager, DerivedManager>) && (ConstructibleWith<DerivedManager, Args...>)
class ManagerCreator
{
private:
    std::shared_ptr<DerivedManager> m_instance;
    void create(Args &...args);

public:
    ManagerCreator() = default;
    ~ManagerCreator() = default;

    std::shared_ptr<DerivedManager> getInstance(Args &...args);
};

#include "ManagerCreator.hpp"

// using CameraManagerCreator = ManagerCreator<BaseManager, CameraManager>
using DrawManagerCreator = ManagerCreator<BaseManager, DrawManager>;
using LoadManagerCreator = ManagerCreator<BaseManager, LoadManager>;
using SceneManagerCreator = ManagerCreator<BaseManager, SceneManager>;
using TransformManagerCreator = ManagerCreator<BaseManager, TransformManager>;
