#include "ModelReader.h"

ModelReader::ModelReader(std::shared_ptr<BaseModelReaderImpl> impl) : m_impl(impl) { }

std::shared_ptr<std::vector<Vertex>> ModelReader::readVertices()
{
    return m_impl->readVertices();
}

std::shared_ptr<std::vector<Edge>> ModelReader::readEdges()
{
    return m_impl->readEdges();
}
