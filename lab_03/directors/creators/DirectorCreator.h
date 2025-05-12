#pragma once

#include "../../concepts/concepts.h"
#include "../../ids/ids.h"
#include "../BaseDirector.h"

#include <any>
#include <memory>

// class BaseDirectorCreator
// {
// public:
//     BaseDirectorCreator() = default;
//     virtual ~BaseDirectorCreator() = default;

//     virtual std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseReader> reader) = 0;
// };

// template <typename Director>
// class DirectorCreatorTemplate : public BaseDirectorCreator
// {
// public:
//     DirectorCreatorTemplate() = default;
//     virtual ~DirectorCreatorTemplate() = default;

//     virtual std::shared_ptr<Director> create(std::shared_ptr<BaseReader> reader) = 0;
// };

// Type Erasure
// class BaseDirectorCreator
// {
// public:
//     BaseDirectorCreator() = default;
//     virtual ~BaseDirectorCreator() = default;

//     virtual std::shared_ptr<BaseDirector> create(const std::vector<std::any> &args) = 0;
// };

// template <typename BaseDirector, typename DerivedDirector, typename... Args>
//     requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
// class DirectorCreatorTemplate : public BaseDirectorCreator
// {
// public:
//     DirectorCreatorTemplate() = default;
//     virtual ~DirectorCreatorTemplate() = default;

//     virtual std::shared_ptr<BaseDirector> create(const std::vector<std::any> &args) = 0;
// };

// // class BaseDirectorCreator
// {
// public:
//     BaseDirectorCreator() = default;
//     virtual ~BaseDirectorCreator() = default;

//     // virtual std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseReader> reader) = 0;

//     template <typename DerivedDirector, typename... Args>
//         requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
//     static std::shared_ptr<BaseDirector> create(Args &&...args);
// };

// template <typename DerivedDirector, typename... Args>
//     requires Derivative<DerivedDirector, BaseDirector> && ConstructibleWith<DerivedDirector, Args...>
// class ConcreteDirectorCreator : public BaseDirectorCreator<Args...>
// {
// public:
//     std::shared_ptr<BaseDirector> create(Args... args) const override
//     {
//         return std::make_shared<DerivedDirector>(std::forward<Args>(args)...);
//     }
// };

// template <typename DerivedDirector>
//     requires Derivative<DerivedDirector, BaseDirector>
// class BaseDirectorCreator
// {
// public:
//     BaseDirectorCreator() = default;
//     virtual ~BaseDirectorCreator() = default;

//     // virtual std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseReader> reader) = 0;

//     template <typename... Args>
//         requires ConstructibleWith<DerivedDirector, Args...>
//     std::shared_ptr<BaseDirector> create(Args &&...args)
//     {
//         return std::make_shared<DerivedDirector>(std::forward<Args>(args)...);
//     }
// };

// template <typename BaseDirector, typename DerivedDirector>
//     requires Derivative<DerivedDirector, BaseDirector>
// class DirectorCreatorTemplate : BaseDirectorCreator
// {
// public:
//     DirectorCreatorTemplate() = default;
//     ~DirectorCreatorTemplate() = default;

//     template <typename... Args>
//         requires ConstructibleWith<DerivedDirector, Args...>
//     static std::shared_ptr<BaseDirector> create(Args &&...args)
//     {
//         return std::make_shared<DerivedDirector>(std::forward<Args>(args)...);
//     }
// };
