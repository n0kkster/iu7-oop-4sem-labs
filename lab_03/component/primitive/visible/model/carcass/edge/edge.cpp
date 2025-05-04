#include "edge.h"

Edge::Edge(size_t start, size_t end) : m_start(start), m_end(end) { }

size_t Edge::getStart() const { return this->m_start; }

size_t Edge::getEnd() const { return this->m_end; }

void Edge::setStart(size_t start) { this->m_start = start; }

void Edge::setEnd(size_t end) { this->m_end = end; }
