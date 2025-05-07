#include "ObjCarcassReader.h"

#include <iostream>

ObjCarcassReader::ObjCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    this->m_file.open(this->m_filename, std::ios::in);
}

std::shared_ptr<std::vector<Vertex>> ObjCarcassReader::readVertices()
{
    std::cout << "in ObjCarcassReader::readVertices()\n";
    return nullptr;
}

std::shared_ptr<std::vector<Edge>> ObjCarcassReader::readEdges()
{
    std::cout << "in ObjCarcassReader::readEdges()\n";
    return nullptr;
}

ObjCarcassReader::~ObjCarcassReader()
{
    m_file.close();
}
