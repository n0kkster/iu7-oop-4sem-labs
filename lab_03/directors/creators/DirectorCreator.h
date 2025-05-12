#pragma once

#include <memory>
#include "../../concepts/concepts.h"
#include "../BaseDirector.h"

class BaseDirectorCreator
{
public:
    BaseDirectorCreator() = default;
    virtual ~BaseDirectorCreator() = default;

    virtual std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseReader> reader) = 0;
};

template <typename Director>
class DirectorCreatorTemplate : public BaseDirectorCreator
{
public:
    DirectorCreatorTemplate() = default;
    virtual ~DirectorCreatorTemplate() = default;

    virtual std::shared_ptr<Director> create(std::shared_ptr<BaseReader> reader) = 0;
};

// class DirectorCreator
// {
// public:
//     DirectorCreator() = default;
//     ~DirectorCreator() = default;

//     template <typename BaseDirector, typename DerivedDirector, typename... Args>
//         requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
//     static std::shared_ptr<BaseDirector> create(Args &&...args)
//     {
//         return std::make_shared<DerivedDirector>(std::forward<Args>(args)...);
//     }
// };

