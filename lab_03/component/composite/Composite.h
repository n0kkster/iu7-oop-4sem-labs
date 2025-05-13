#pragma once

#include "../BaseObject.h"

#include <cstddef>

class Composite final : public BaseObject
{
private:
    mapObjects m_objects;
    size_t m_count;

public:
    Composite() = default;
    Composite(const mapObjects &objects);

    iterator begin() override;
    iterator end() override;

    std::shared_ptr<BaseObject> getObject(const size_t id) const override;
    void add(std::shared_ptr<BaseObject> object) override;
    void remove(const size_t id) noexcept override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;

    Vertex getCenter() const noexcept override;

    bool isComposite() const noexcept override;

    bool isVisible() const noexcept override;
};
