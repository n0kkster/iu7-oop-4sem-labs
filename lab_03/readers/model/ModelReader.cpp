#include "ModelReader.h"

#include "../../builders/model/carcass/CarcassModelBuilder.h"

#include <algorithm>

// TODO: MAP INSTEAD OF SWITCH
void ModelReader::read(BaseBuilder &builder, size_t part)
{
    auto cv = dynamic_cast<CarcassModelBuilder &>(builder);
    switch (part)
    {
        case VERTICES:
            std::ranges::for_each(this->readVertices(),
                                  [&cv](const auto &v) { cv.m_structure->addVertex(v); });
            break;
        case EDGES:
            std::ranges::for_each(this->readEdges(), [&cv](const auto &e) { cv.m_structure->addEdge(e); });
    }
}
