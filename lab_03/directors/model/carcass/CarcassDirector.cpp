#include "CarcassDirector.h"
#include <memory>
#include "../../../builders/model/carcass/CarcassModelBuilder.h"

CarcassDirector::CarcassDirector(std::shared_ptr<BaseReader> reader, InternalRepresentationId repr)
{
    m_builder = std::make_shared<CarcassModelBuilder>(reader, repr);
}

std::shared_ptr<BaseObject> CarcassDirector::create() const
{
    return m_builder->getProduct();
}