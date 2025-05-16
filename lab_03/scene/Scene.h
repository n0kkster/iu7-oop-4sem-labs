#pragma once

#include "../component/BaseObject.h"
#include <memory>

class Scene
{
private:
    size_t m_objcount;
    mapObjects m_objects;

    Scene() = default;

public:
    using iterator = mapObjects::iterator;

    Scene(const Scene &other) = delete;
    Scene(Scene &&other) = delete;

    ~Scene() = default;

    static std::shared_ptr<Scene> getInstance();

    iterator begin();
    iterator end();

    size_t addComponent(std::shared_ptr<BaseObject> object);
    std::shared_ptr<BaseObject> getComponent(size_t id);
    void removeComponent(size_t id);

    void accept(std::shared_ptr<BaseVisitor> visitor);
};
