#include "CarcassModel.h"

CarcassModel::CarcassModel(std::shared_ptr<BaseStructure> structure) : m_structure(structure) { }

Vertex CarcassModel::getCenter() const noexcept
{
    return m_structure->getCenter();
}

std::shared_ptr<BaseStructure> CarcassModel::getStructure() const
{
    return this->m_structure;
}
