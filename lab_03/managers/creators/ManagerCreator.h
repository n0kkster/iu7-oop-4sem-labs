#pragma once

#include "../../concepts/concepts.h"
#include "../BaseManager.h"
#include "../camera/CameraManager.h"
#include "../draw/DrawManager.h"
#include "../load/LoadManager.h"
#include "../scene/SceneManager.h"
#include "../transform/TransformManager.h"

#include <memory>

template <typename BaseManager, typename DerivedManager, typename... Args>
    requires(Derivative<DerivedManager, BaseManager>) && (ConstructibleWith<DerivedManager, Args...>)
class ManagerCreator
{

public:
    ManagerCreator() = default;
    ~ManagerCreator() = default;

    template <typename... CallArgs>
        requires(IsSupportedArg<CallArgs, Args...> && ...)
    std::shared_ptr<DerivedManager> getInstance(CallArgs &&...args);
};

#include "ManagerCreator.hpp"

using CameraManagerCreator = ManagerCreator<BaseManager, CameraManager>;
using DrawManagerCreator = ManagerCreator<BaseManager, DrawManager>;
using LoadManagerCreator = ManagerCreator<BaseManager, LoadManager>;
using SceneManagerCreator = ManagerCreator<BaseManager, SceneManager>;
using TransformManagerCreator = ManagerCreator<BaseManager, TransformManager>;
