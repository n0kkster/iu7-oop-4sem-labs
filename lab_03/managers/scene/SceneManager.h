#pragma once

#include "../../scene/Scene.h"
#include "../BaseManager.h"

#include <memory>
#include <vector>

class SceneManager : public BaseManager
{
private:
    std::unique_ptr<Scene> m_scene;

public:
    SceneManager();
    virtual ~SceneManager() = default;

    std::shared_ptr<BaseObject> getObject(size_t id);
    size_t addObject(std::shared_ptr<BaseObject> object);
    void removeObject(size_t id);

    size_t compose(std::vector<size_t> ids);

    void accept(std::shared_ptr<BaseVisitor> visitor);
};
