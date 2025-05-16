#include "CarcassModelBuilder.h"

#include "../../../component/primitive/visible/model/carcass/CarcassModel.h"
#include "../../../exceptions/model/carcass/CarcassException.h"

CarcassModelBuilder::CarcassModelBuilder(std::shared_ptr<CarcassReader> reader,
                                         InternalRepresentationId repr) : BaseModelBuilder(reader)
{
    m_part = 0;

    if (auto it = m_reprMap.find(repr); it != m_reprMap.end())
        m_structure = it->second();
    else
        throw CarcassInvalidRepresentation("Invalid representation chosen!");
}

bool CarcassModelBuilder::buildVertices()
{
    if (m_part != VERTICES)
        return false;

    auto vertices = m_reader->readVertices();

    std::ranges::for_each(*vertices, [this](const Vertex &v) { this->m_structure->addVertex(v); });

    ++m_part;
    return true;
}

bool CarcassModelBuilder::buildEdges()
{
    if (m_part != EDGES)
        return false;

    auto edges = m_reader->readEdges();
    std::ranges::for_each(*edges, [this](const Edge &e) { this->m_structure->addEdge(e); });

    ++m_part;
    return true;
}

bool CarcassModelBuilder::buildCenter()
{
    if (m_part != CENTER)
        return false;

    double xmin, ymin, zmin, xmax, ymax, zmax;

    const auto &vertices = m_structure->getVertices();
    xmin = vertices[0].getX();
    xmax = vertices[0].getX();
    ymin = vertices[0].getY();
    ymax = vertices[0].getY();
    zmin = vertices[0].getZ();
    zmax = vertices[0].getZ();

    for (const auto &v : vertices)
    {
        xmin = std::min(v.getX(), xmin);
        xmax = std::max(v.getX(), xmax);

        ymin = std::min(v.getY(), ymin);
        ymax = std::max(v.getY(), ymax);

        zmin = std::min(v.getZ(), zmin);
        zmax = std::max(v.getZ(), zmax);
    }

    m_structure->setCenter({ (xmin + xmax) / 2, (ymin + ymax) / 2, (zmin + zmax) / 2 });

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
