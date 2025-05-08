#include "CsvCarcassReader.h"

#include <iostream>

CsvCarcassReader::CsvCarcassReader(const std::string &filename) : CarcassReader(filename)
{
    m_file.open(m_filename, std::ios::in);
}

std::vector<Vertex> CsvCarcassReader::readVertices()
{
    std::cout << "in CsvCarcassReader::readVertices()\n";
    return {};
}

std::vector<Edge> CsvCarcassReader::readEdges()
{
    std::cout << "in CsvCarcassReader::readEdges()\n";
    return {};
}

CsvCarcassReader::~CsvCarcassReader()
{
    m_file.close();
}
