#include "CarcassDirector.h"
#include <memory>
#include "../../../builders/model/carcass/CarcassModelBuilder.h"

CarcassDirector::CarcassDirector(std::shared_ptr<CarcassReader> reader)
{
    m_builder = std::make_shared<CarcassModelBuilder>(reader);
}

std::shared_ptr<BaseObject> CarcassDirector::create() const
{
    return m_builder->getProduct();
}