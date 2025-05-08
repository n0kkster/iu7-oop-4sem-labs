#include "ObjCarcassReader.h"

#include <iostream>

ObjCarcassReader::ObjCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    m_file.open(m_filename, std::ios::in);
}

std::vector<Vertex> ObjCarcassReader::readVertices()
{
    std::cout << "in ObjCarcassReader::readVertices()\n";
    return {};
}

std::vector<Edge> ObjCarcassReader::readEdges()
{
    std::cout << "in ObjCarcassReader::readEdges()\n";
    return {};
}

ObjCarcassReader::~ObjCarcassReader()
{
    m_file.close();
}
