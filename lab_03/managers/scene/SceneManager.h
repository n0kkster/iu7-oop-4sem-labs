#pragma once

#include "../../scene/Scene.h"
#include "../BaseManager.h"

#include <memory>
#include <vector>

class SceneManager : public BaseManager
{
private:
    std::shared_ptr<Scene> m_scene;

public:
    SceneManager();
    virtual ~SceneManager() = default;

    std::shared_ptr<BaseObject> getObject(size_t id);
    void addObject(std::shared_ptr<BaseObject> object);
    void removeObject(size_t id);
    void getCenter(size_t id, Vertex &center) const;

    void compose(std::vector<size_t> ids);

    void accept(std::shared_ptr<BaseVisitor> visitor);
};
