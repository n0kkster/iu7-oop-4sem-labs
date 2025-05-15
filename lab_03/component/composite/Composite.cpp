#include "Composite.h"

#include "../../exceptions/composite/CompositeException.h"

#include <memory>
#include <stdexcept>

Composite::Composite(const mapObjects &objects) : m_objects(objects) { }

typename Composite::iterator Composite::begin()
{
    return m_objects.begin();
}

typename Composite::iterator Composite::end()
{
    return m_objects.end();
}

typename Composite::const_iterator Composite::begin() const
{
    return m_objects.begin();
}

typename Composite::const_iterator Composite::end() const
{
    return m_objects.end();
}

Vertex Composite::getCenter() const noexcept
{
    Vertex center = {0, 0, 0};
    size_t count = 0;

    for (auto it = begin(); it != end(); ++it)
    {
        center += it->second->getCenter();
        ++count;
    }

    return {center.getX() / (double)count, center.getY() / (double)count, center.getZ() / (double)count};
}

bool Composite::isComposite() const noexcept
{
    return true;
}

bool Composite::isVisible() const noexcept
{
    return false;
}

void Composite::add(std::shared_ptr<BaseObject> object)
{
    m_objects[m_count++] = object;
}

void Composite::remove(const size_t id) noexcept
{
    m_objects.erase(id);
}

std::shared_ptr<BaseObject> Composite::getObject(const size_t id) const
{
    std::shared_ptr<BaseObject> obj;
    try
    {
        obj = m_objects.at(id);
    }
    catch (const std::out_of_range &ex)
    {
        throw CompositeOutOfRangeException("Composite index out of range!");
    }
    return obj;
}

void Composite::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &[id, component] : m_objects)
        component->accept(visitor);
}