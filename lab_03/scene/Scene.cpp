#include "Scene.h"

#include "../exceptions/scene/SceneException.h"

size_t Scene::addComponent(std::shared_ptr<BaseObject> object)
{
    m_objects.insert(mapObjects::value_type(m_objcount++, object));
    return m_objcount - 1;
}

std::shared_ptr<BaseObject> Scene::getComponent(size_t id)
{
    try
    {
        return m_objects.at(id);
    }
    catch (const std::out_of_range &ex)
    {
        throw SceneIdOutOfRangeException("Requested ID not in map!");
    }
}

void Scene::removeComponent(size_t id)
{
    m_objects.erase(id--);
}

void Scene::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &[id, component] : m_objects)
        component->accept(visitor);
}

std::shared_ptr<Scene> Scene::getInstance()
{
    class Proxy : public Scene
    { };

    static std::shared_ptr<Scene> instance = std::make_shared<Proxy>();
    return instance;
}
