#pragma once

#include "../BaseModel.h"
#include "../vertex/vertex.h"
#include "../structure/BaseStructure.h"

#include <memory>

class CarcassModel final : public BaseModel
{
public:
    CarcassModel() = default;
    explicit CarcassModel(std::shared_ptr<BaseStructure> structure);

    virtual ~CarcassModel() override = default;

    Vertex getCenter() const noexcept override;

    // void accept(/* visitor */) override;

    std::shared_ptr<BaseStructure> getStructure() const override;
};
