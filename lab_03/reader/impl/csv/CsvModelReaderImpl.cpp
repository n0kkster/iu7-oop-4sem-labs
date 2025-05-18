#include "CsvModelReaderImpl.h"

#include "../../../exceptions/model/ModelException.h"

#include <sstream>
#include <string>

CsvModelReaderImpl::CsvModelReaderImpl(const std::string &filename) : BaseModelReaderImpl(filename) { }

std::shared_ptr<std::vector<Vertex>> CsvModelReaderImpl::readVertices()
{
    std::vector<Vertex> vertices;
    std::string line;
    double x, y, z;
    char comma;

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    std::getline(m_file, line);

    while (std::getline(m_file, line))
    {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        if (iss >> x >> comma >> y >> comma >> z)
            vertices.emplace_back(x, y, z);
        else
            break;
    }

    if (vertices.empty())
        throw ModelInvalidVerticesCountException("No vertices found in CSV file!");

    return std::make_shared<std::vector<Vertex>>(vertices);
}

std::shared_ptr<std::vector<Edge>> CsvModelReaderImpl::readEdges()
{
    std::vector<Edge> edges;
    std::string line;
    size_t id1, id2;
    char comma;

    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    while (std::getline(m_file, line))
    {
        std::istringstream iss(line);
        double x, y, z;
        if (!(iss >> x >> comma >> y >> comma >> z))
            break;
    }

    do
    {
        if (line.empty())
            continue;

        std::istringstream iss(line);
        if (iss >> id1 >> comma >> id2)
            edges.emplace_back(id1, id2);
    } while (std::getline(m_file, line));

    return std::make_shared<std::vector<Edge>>(edges);
}
