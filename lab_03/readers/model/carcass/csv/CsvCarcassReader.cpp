#include "CsvCarcassReader.h"

#include <iostream>

CsvCarcassReader::CsvCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    this->m_file.open(this->m_filename, std::ios::in);
}

std::shared_ptr<std::vector<Vertex>> CsvCarcassReader::readVertices()
{
    std::cout << "in CsvCarcassReader::readVertices()\n";
    return nullptr;
}

std::shared_ptr<std::vector<Edge>> CsvCarcassReader::readEdges()
{
    std::cout << "in CsvCarcassReader::readEdges()\n";
    return nullptr;
}

CsvCarcassReader::~CsvCarcassReader()
{
    m_file.close();
}
