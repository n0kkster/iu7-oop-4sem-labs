#pragma once

#include "../BaseModel.h"
#include "../vertex/Vertex.h"
#include "../structure/BaseStructure.h"

#include <memory>

class CarcassModel final : public BaseModel
{
public:
    CarcassModel() = default;
    explicit CarcassModel(std::shared_ptr<BaseStructure> structure);

    virtual ~CarcassModel() override = default;

    Vertex getCenter() const noexcept override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;

    std::shared_ptr<BaseStructure> getStructure() const override;
};
