#include "CarcassModel.h"

CarcassModel::CarcassModel(std::shared_ptr<BaseStructure> structure) : BaseModel(structure) { }

Vertex CarcassModel::getCenter() const noexcept
{
    return m_structure->getCenter();
}

std::shared_ptr<BaseStructure> CarcassModel::getStructure() const
{
    return m_structure;
}

void CarcassModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(this->getStructure());
}