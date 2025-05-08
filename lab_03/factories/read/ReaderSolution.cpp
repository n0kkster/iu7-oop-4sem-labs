#include "ReaderSolution.h"

ReaderSolution::ReaderSolution(std::initializer_list<std::pair<size_t, ReaderCreator>> ilist)
{
    for (auto &&p : ilist)
        this->registrate(p.first, p.second);
}

bool ReaderSolution::registrate(size_t id, ReaderCreator creatorFunc)
{
    return this->m_callbacks.insert(CallbackMap::value_type(id, creatorFunc)).second;
}

std::unique_ptr<BaseReaderCreator> ReaderSolution::create(size_t id) const
{
    auto it = this->m_callbacks.find(id);
    
    if (it == this->m_callbacks.end())
        return nullptr;

    return it->second();
}