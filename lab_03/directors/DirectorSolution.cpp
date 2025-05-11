#include "DirectorSolution.h"

DirectorSolution::DirectorSolution(std::initializer_list<std::pair<size_t, DirectorCreator>> ilist)
{
    for (auto &&p : ilist)
        registrate(p.first, p.second);
}

bool DirectorSolution::registrate(size_t id, DirectorCreator creatorFunc)
{
    return m_callbacks.insert(CallbackMap::value_type(id, creatorFunc)).second;
}

std::unique_ptr<BaseDirectorCreator> DirectorSolution::create(size_t id) const
{
    auto it = m_callbacks.find(id);
    
    if (it == m_callbacks.end())
        return nullptr;

    return it->second();
}