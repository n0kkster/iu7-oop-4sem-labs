#include "ModelDirector.h"

ModelDirector::ModelDirector(std::shared_ptr<BaseModelBuilder> builder) : BaseDirector(builder) { }

std::shared_ptr<BaseObject> ModelDirector::create() const
{
    return m_builder->getProduct();
}