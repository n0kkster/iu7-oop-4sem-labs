#include "TxtCarcassReader.h"
#include "../../../../exceptions/model/carcass/CarcassException.h"

TxtCarcassReader::TxtCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    m_file.open(m_filename, std::ios::in);
}

std::vector<Vertex> TxtCarcassReader::readVertices()
{
    size_t verticesCount;
    double x, y, z;

    m_vertices.clear();

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    if (!(m_file >> verticesCount))
        throw CarcassInvalidStructureException("File should contain vertices count on first line!");

    if (verticesCount <= 0)
        throw CarcassInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    m_vertices.resize(verticesCount);
    
    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(m_file >> x >> y >> z))
            throw CarcassInvalidVertexException("File contains invalid vertex!");

        m_vertices[i] = Vertex(x, y, z);
    }

    return m_vertices;
}

std::vector<Edge> TxtCarcassReader::readEdges()
{
    size_t verticesCount, edgesCount;
    size_t id1, id2;
    double x, y, z;

    m_edges.clear();

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    if (!(m_file >> verticesCount))
        throw CarcassInvalidStructureException("File should contain vertices count on first line!");
    
    if (verticesCount <= 0)
        throw CarcassInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(m_file >> x >> y >> z))
            throw CarcassInvalidVertexException("File contains invalid vertex!");
    }

    if (!(m_file >> edgesCount))
        throw CarcassInvalidStructureException("File should contain edges count after vertices!");

    m_edges.resize(edgesCount);

    for (size_t i = 0; i < edgesCount; ++i)
    {
        if (!(m_file >> id1 >> id2))
            throw CarcassInvalidEdgeException("File contains invalid edge!");

        m_edges[i] = Edge(id1, id2);
    }

    return m_edges;
}

TxtCarcassReader::~TxtCarcassReader()
{
    m_file.close();
}
