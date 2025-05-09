#pragma once

#include "../VisibleObject.h"
#include "structure/BaseStructure.h"

#include <memory>

class BaseModel : public VisibleObject
{
protected:
    std::shared_ptr<BaseStructure> m_structure;

public:
    BaseModel() = default;

    explicit BaseModel(std::shared_ptr<BaseStructure> structure) : m_structure(structure) { }

    virtual ~BaseModel() override = default;

    virtual std::shared_ptr<BaseStructure> getStructure() const = 0;
};
