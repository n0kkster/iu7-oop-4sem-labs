#pragma once

#include "../visitors/BaseVisitor.h"
#include "primitive/visible/model/vertex/Vertex.h"

#include <cstddef>
#include <map>
#include <memory>

class BaseObject;
using mapObjects = std::map<size_t, std::shared_ptr<BaseObject>>;

class BaseObject
{
public:
    using iterator = mapObjects::iterator;

    BaseObject() = default;
    virtual ~BaseObject() = default;

    virtual iterator begin();
    virtual iterator end();

    virtual std::shared_ptr<BaseObject> getObject(const size_t id) const;
    virtual void add(std::shared_ptr<BaseObject> object);
    virtual void remove(const size_t id) noexcept;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

    virtual Vertex getCenter() const noexcept;
    virtual bool isComposite() const noexcept = 0;
    virtual bool isVisible() const noexcept = 0;
};
