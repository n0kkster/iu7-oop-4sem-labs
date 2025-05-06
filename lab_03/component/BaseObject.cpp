#include "BaseObject.h"

typename BaseObject::iterator BaseObject::begin()
{
    return iterator();
}

typename BaseObject::iterator BaseObject::end()
{
    return iterator();
}

void BaseObject::add(std::shared_ptr<BaseObject>) { }

void BaseObject::remove(size_t id) noexcept
{
    (void)id;
}

std::shared_ptr<BaseObject> BaseObject::getObject(size_t id) const
{
    (void)id;
    return nullptr;
}

Vertex BaseObject::getCenter() const noexcept
{
    return { 0, 0, 0 };
}
