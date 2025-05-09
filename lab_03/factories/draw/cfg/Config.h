#pragma once

enum FactoryType
{
    QT = 0,
};

class Config
{
private:
    FactoryType m_type;

public:
    Config();
    Config(const FactoryType &type);

    ~Config() = default;

    void setFactoryType(const FactoryType &type);
    FactoryType getFactoryType() const noexcept;
};
