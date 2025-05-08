#include "CarcassModelBuilder.h"
#include "../../../component/primitive/visible/model/carcass/CarcassModel.h"

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
    return std::make_shared<CarcassModel>(m_structure);
}