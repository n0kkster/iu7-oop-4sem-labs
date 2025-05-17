#include "CarcassReader.h"

#include "../../../strategies/read/solution/CarcassReadStrategySolution.h"

CarcassReader::CarcassReader(const std::string &filename) : ModelReader(filename)
{
    CarcassReadStrategySolution solution;

    m_file = std::make_shared<std::ifstream>(filename, std::ios::in);
    m_strategy = solution.create(filename, m_file);
}

std::shared_ptr<std::vector<Vertex>> CarcassReader::readVertices()
{
    return m_strategy->readVertices();
}

std::shared_ptr<std::vector<Edge>> CarcassReader::readEdges()
{
    return m_strategy->readEdges();
}

CarcassReader::~CarcassReader()
{
    m_file->close();
}
