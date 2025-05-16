// CsvCarcassReadStrategy.cpp
#include "CsvCarcassReadStrategy.h"

#include "../../../exceptions/model/carcass/CarcassException.h"

#include <sstream>
#include <string>

CsvCarcassReadStrategy::CsvCarcassReadStrategy(std::shared_ptr<std::ifstream> file) :
    BaseCarcassReadStrategy(file)
{ }

std::shared_ptr<std::vector<Vertex>> CsvCarcassReadStrategy::readVertices()
{
    std::vector<Vertex> vertices;
    std::string line;
    double x, y, z;
    char comma;

    m_file->clear();
    m_file->seekg(0, std::ios::beg);

    // Пропускаем заголовок, если есть
    std::getline(*m_file, line);

    while (std::getline(*m_file, line))
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
        throw CarcassInvalidVerticesCountException("No vertices found in CSV file!");

    return std::make_shared<std::vector<Vertex>>(vertices);
}

std::shared_ptr<std::vector<Edge>> CsvCarcassReadStrategy::readEdges()
{
    std::vector<Edge> edges;
    std::string line;
    size_t id1, id2;
    char comma;

    m_file->clear();
    m_file->seekg(0, std::ios::beg);

    while (std::getline(*m_file, line))
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
    } while (std::getline(*m_file, line));

    return std::make_shared<std::vector<Edge>>(edges);
}
