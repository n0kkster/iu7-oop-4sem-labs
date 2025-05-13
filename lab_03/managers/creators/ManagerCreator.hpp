#pragma once

#include "ManagerCreator.h"

template <typename BaseManager, typename DerivedManager, typename... Args>
    requires(std::is_base_of_v<BaseManager, DerivedManager>) && (ConstructibleWith<DerivedManager, Args...>)
void ManagerCreator<BaseManager, DerivedManager, Args...>::create(Args &...args)
{
    m_instance = std::make_shared<DerivedManager>(std::forward<Args>(args)...);
}

template <typename BaseManager, typename DerivedManager, typename... Args>
    requires(std::is_base_of_v<BaseManager, DerivedManager>) && (ConstructibleWith<DerivedManager, Args...>)
std::shared_ptr<DerivedManager> ManagerCreator<BaseManager, DerivedManager, Args...>::getInstance(Args &...args)
{
    if (!m_instance)
        create();
    
    return m_instance;
}