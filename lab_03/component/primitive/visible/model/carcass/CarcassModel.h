#pragma once

#include "../BaseModel.h"
#include "structure/BaseStructure.h"
#include "../vertex/vertex.h"

#include <memory>

class CarcassModel final : public BaseModel
{
private:
    std::shared_ptr<BaseStructure> m_structure;

public:
    CarcassModel() = default;
    explicit CarcassModel(std::shared_ptr<BaseStructure> structure);

    virtual ~CarcassModel() override = default;

    Vertex getCenter() const noexcept override;

    // void accept(/* visitor */) override;

    std::shared_ptr<BaseStructure> getStructure() const;
};
