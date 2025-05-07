#include "TxtCarcassReader.h"
#include "../../../../exceptions/model/carcass/CarcassException.h"

TxtCarcassReader::TxtCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    this->m_file.open(this->m_filename, std::ios::in);
}

std::shared_ptr<std::vector<Vertex>> TxtCarcassReader::readVertices()
{
    size_t verticesCount;
    double x, y, z;

    this->m_vertices.clear();

    this->m_file.clear();
    this->m_file.seekg(0, std::ios::beg);

    if (!(this->m_file >> verticesCount))
        throw CarcassInvalidStructureException("File should contain vertices count on first line!");

    if (verticesCount <= 0)
        throw CarcassInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    this->m_vertices.resize(verticesCount);
    
    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(this->m_file >> x >> y >> z))
            throw CarcassInvalidVertexException("File contains invalid vertex!");

        this->m_vertices[i] = Vertex(x, y, z);
    }

    return std::make_shared<std::vector<Vertex>>(this->m_vertices);
}

std::shared_ptr<std::vector<Edge>> TxtCarcassReader::readEdges()
{
    size_t verticesCount, edgesCount;
    size_t id1, id2;
    double x, y, z;

    this->m_edges.clear();

    this->m_file.clear();
    this->m_file.seekg(0, std::ios::beg);

    if (!(this->m_file >> verticesCount))
        throw CarcassInvalidStructureException("File should contain vertices count on first line!");
    
    if (verticesCount <= 0)
        throw CarcassInvalidVerticesCountException("Invalid vertices count! Should be > 0!");

    for (size_t i = 0; i < verticesCount; ++i)
    {
        if (!(this->m_file >> x >> y >> z))
            throw CarcassInvalidVertexException("File contains invalid vertex!");
    }

    if (!(this->m_file >> edgesCount))
        throw CarcassInvalidStructureException("File should contain edges count after vertices!");

    this->m_edges.resize(edgesCount);

    for (size_t i = 0; i < edgesCount; ++i)
    {
        if (!(this->m_file >> id1 >> id2))
            throw CarcassInvalidEdgeException("File contains invalid edge!");

        this->m_edges[i] = Edge(id1, id2);
    }

    return std::make_shared<std::vector<Edge>>(this->m_edges);
}

TxtCarcassReader::~TxtCarcassReader()
{
    m_file.close();
}
