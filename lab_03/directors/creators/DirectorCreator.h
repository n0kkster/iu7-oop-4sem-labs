#pragma once

#include <memory>

class BaseDirectorCreator
{
public:
    BaseDirectorCreator() = default;
    virtual ~BaseDirectorCreator() = default;
};

template <typename Director, typename... Args>
class DirectorCreatorTemplate : public BaseDirectorCreator
{
public:
    DirectorCreatorTemplate() = default;
    virtual ~DirectorCreatorTemplate() = default;

    virtual std::shared_ptr<Director> create(Args &&...args) = 0;
};

