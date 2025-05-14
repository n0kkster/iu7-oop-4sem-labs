#include "CarcassModelBuilder.h"

#include "../../../component/primitive/visible/model/carcass/CarcassModel.h"

#include <stdexcept>

CarcassModelBuilder::CarcassModelBuilder(std::shared_ptr<BaseReader> reader, InternalRepresentationId repr) :
    BaseModelBuilder(reader)
{
    m_part = 0;
    
    if (auto it = m_reprMap.find(repr); it != m_reprMap.end())
        m_structure = it->second();
    else
        throw std::runtime_error("Error invalid repr!");
}

bool CarcassModelBuilder::buildVertices()
{
    if (m_part != VERTICES)
        return false;

    m_reader->read(*this, m_part);

    ++m_part;
    return true;
}

bool CarcassModelBuilder::buildEdges()
{
    if (m_part != EDGES)
        return false;

    m_reader->read(*this, m_part);

    ++m_part;
    return true;
}

bool CarcassModelBuilder::buildCenter()
{
    if (m_part != CENTER)
        return false;

    m_part = VERTICES;
    return true;
}

std::shared_ptr<BaseObject> CarcassModelBuilder::createProduct()
{
    if (!this->buildVertices())
        return nullptr;

    if (!this->buildEdges())
        return nullptr;

    if (!this->buildCenter())
        return nullptr;

    return std::make_shared<CarcassModel>(m_structure);
}
