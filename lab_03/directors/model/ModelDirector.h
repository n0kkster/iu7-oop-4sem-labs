#pragma once

#include "../BaseDirector.h"
#include "../../builders/model/BaseModelBuilder.h"

class ModelDirector : public BaseDirector
{
public:
    ModelDirector() = delete;
    ModelDirector(std::shared_ptr<BaseModelBuilder> builder);
    virtual ~ModelDirector() override = default;

    std::shared_ptr<BaseObject> create() const override;
};