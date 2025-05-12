#pragma once

#include "../../concepts/concepts.h"
#include "creators/BaseReaderCreator.h"
#include "creators/ConcreteReaderCreator.h"
#include <initializer_list>

#include <cstddef>
#include <map>
#include <memory>

class ReaderCreatorMaker
{
public:
    template <Derivative<BaseReader> ConcreteReader>
    static std::unique_ptr<BaseReaderCreator> createReaderCreator()
        requires Derivative<ConcreteReader, BaseReader> && NotAbstract<ConcreteReader>
              /* && ConstructibleWith<ConcreteReader> */
    {
        return std::make_unique<ConcreteReaderCreator<BaseReader, ConcreteReader>>();
    }
};

class ReaderSolution
{
public:
    using ReaderCreator = std::unique_ptr<BaseReaderCreator> (&)();
    using CallbackMap = std::map<size_t, ReaderCreator>;

public:
    ReaderSolution() = default;
    ReaderSolution(std::initializer_list<std::pair<size_t, ReaderCreator>> ilist);

    ~ReaderSolution() = default;

    bool registrate(size_t id, ReaderCreator creatorFunc);
    std::unique_ptr<BaseReaderCreator> create(size_t id) const;

private:
    CallbackMap m_callbacks;
};
