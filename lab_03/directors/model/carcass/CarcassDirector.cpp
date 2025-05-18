#include "CarcassDirector.h"
#include <memory>

CarcassDirector::CarcassDirector(std::shared_ptr<BaseBuilder> builder)
{
    m_builder = builder;
}

std::shared_ptr<BaseObject> CarcassDirector::create() const
{
    return m_builder->getProduct();
}