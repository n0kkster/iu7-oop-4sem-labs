#include "BuilderSolution.h"
#include "../../exceptions/model/ModelException.h"
#include "../creator/BuilderCreator.h"

std::shared_ptr<BaseBuilder> BuilderSolution::create(std::shared_ptr<ModelReader> reader, InternalRepresentationId repr)
{
    if (auto it = m_reprMap.find(repr); it != m_reprMap.end())
        return CarcassBuilderCreator::create(reader, it->second());

    throw ModelInvalidRepresentation("Invalid representation chosen!");
}
