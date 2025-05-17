// ObjCarcassReadStrategy.cpp
#include "ObjCarcassReadStrategy.h"

#include "../../../exceptions/model/carcass/CarcassException.h"

#include <sstream>
#include <string>

ObjCarcassReadStrategy::ObjCarcassReadStrategy(std::shared_ptr<std::ifstream> file) :
    BaseCarcassReadStrategy(file)
{ }

std::shared_ptr<std::vector<Vertex>> ObjCarcassReadStrategy::readVertices()
{
    std::vector<Vertex> vertices;
    std::string line;

    m_file->clear();
    m_file->seekg(0, std::ios::beg);

    while (std::getline(*m_file, line))
    {
        if (line.empty() || line[0] != 'v')
            continue;

        std::istringstream iss(line);
        char type;
        double x, y, z;

        if (iss >> type >> x >> y >> z && type == 'v')
            vertices.emplace_back(x, y, z);
    }

    if (vertices.empty())
        throw CarcassInvalidVerticesCountException("No vertices found in OBJ file!");

    return std::make_shared<std::vector<Vertex>>(vertices);
}

std::shared_ptr<std::vector<Edge>> ObjCarcassReadStrategy::readEdges()
{
    std::vector<Edge> edges;
    std::string line;

    m_file->clear();
    m_file->seekg(0, std::ios::beg);

    while (std::getline(*m_file, line))
    {
        if (line.empty() || line[0] != 'f')
            continue;

        std::istringstream iss(line);
        char type;
        std::vector<size_t> vertexIndices;
        size_t index;

        iss >> type;

        while (iss >> index)
        {
            vertexIndices.push_back(index - 1);

            while (iss.peek() == '/' || iss.peek() == ' ')
                iss.ignore();
        }

        for (size_t i = 1; i < vertexIndices.size(); i++)
            edges.emplace_back(vertexIndices[i - 1], vertexIndices[i]);

        if (vertexIndices.size() > 2)
            edges.emplace_back(vertexIndices.back(), vertexIndices.front());
    }

    return std::make_shared<std::vector<Edge>>(edges);
}
