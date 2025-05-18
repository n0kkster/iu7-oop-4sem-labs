#include "TxtModelReaderImpl.h"

#include "../../../exceptions/model/ModelException.h"

TxtModelReaderImpl::TxtModelReaderImpl(const std::string &filename) : BaseModelReaderImpl(filename) { }

std::shared_ptr<std::vector<Vertex>> TxtModelReaderImpl::readVertices()
{
    size_t verticesCount;
    double x, y, z;

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    if (!(m_file >> verticesCount))
        throw ModelInvalidStructureException("File should contain vertices count on first line!");

    if (verticesCount <= 0)
        throw ModelInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    std::vector<Vertex> vertices(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(m_file >> x >> y >> z))
            throw ModelInvalidVertexException("File contains invalid vertex!");

        vertices[i] = Vertex(x, y, z);
    }

    return std::make_shared<std::vector<Vertex>>(vertices);
}

std::shared_ptr<std::vector<Edge>> TxtModelReaderImpl::readEdges()
{
    size_t verticesCount, edgesCount;
    size_t id1, id2;
    double x, y, z;

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    if (!(m_file >> verticesCount))
        throw ModelInvalidStructureException("File should contain vertices count on first line!");

    if (verticesCount <= 0)
        throw ModelInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(m_file >> x >> y >> z))
            throw ModelInvalidVertexException("File contains invalid vertex!");
    }

    if (!(m_file >> edgesCount))
        throw ModelInvalidStructureException("File should contain edges count after vertices!");

    std::vector<Edge> edges(edgesCount);

    for (size_t i = 0; i < edgesCount; ++i)
    {
        if (!(m_file >> id1 >> id2))
            throw ModelInvalidEdgeException("File contains invalid edge!");

        edges[i] = Edge(id1, id2);
    }

    return std::make_shared<std::vector<Edge>>(edges);
}
