#include "CarcassDirector.h"
#include <memory>
#include "../../../builders/model/carcass/CarcassModelBuilder.h"
#include "../../../readers/creator/ReaderCreator.h"

CarcassDirector::CarcassDirector(const std::string &filename, InternalRepresentationId repr)
{
    std::shared_ptr<CarcassReader> reader = CarcassReaderCreator::create(filename);
    m_builder = std::make_shared<CarcassModelBuilder>(reader, repr);
}

std::shared_ptr<BaseObject> CarcassDirector::create() const
{
    return m_builder->getProduct();
}