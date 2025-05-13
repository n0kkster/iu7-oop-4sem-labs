#pragma once

#include "../component/BaseObject.h"

class Scene
{
private:
    size_t m_objcount;
    mapObjects m_objects;

public:
    using iterator = mapObjects::iterator;

    Scene() = default;
    ~Scene() = default;

    iterator begin();
    iterator end();

    size_t addComponent(std::shared_ptr<BaseObject> object);
    std::shared_ptr<BaseObject> getComponent(size_t id);
    void removeComponent(size_t id);

    void accept(std::shared_ptr<BaseVisitor> visitor);
};
