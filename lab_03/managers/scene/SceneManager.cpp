#include "SceneManager.h"
#include "../../component/composite/Composite.h"

SceneManager::SceneManager() : m_scene(std::make_unique<Scene>()) { }

std::shared_ptr<BaseObject> SceneManager::getObject(size_t id)
{
    return m_scene->getComponent(id);
}

size_t SceneManager::addObject(std::shared_ptr<BaseObject> object)
{
    return m_scene->addComponent(object);
}

void SceneManager::removeObject(size_t id)
{
    m_scene->removeComponent(id);
}

size_t SceneManager::compose(std::vector<size_t> ids)
{
    auto composite = std::make_shared<Composite>();

    for (const size_t &id : ids)
        composite->add(m_scene->getComponent(id));

    return m_scene->addComponent(composite);
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor)
{
    m_scene->accept(visitor);
}