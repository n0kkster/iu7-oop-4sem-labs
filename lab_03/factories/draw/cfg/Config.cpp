#include "Config.h"

Config::Config() : m_type(FactoryType::QT) { }

Config::Config(const FactoryType &type) : m_type(type) { }

void Config::setFactoryType(const FactoryType &type)
{
    m_type = type;
}

FactoryType Config::getFactoryType() const noexcept
{
    return m_type;
}
