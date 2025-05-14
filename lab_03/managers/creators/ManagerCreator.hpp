#pragma once

#include "ManagerCreator.h"

template <typename BaseManager, typename DerivedManager, typename... Args>
    requires(std::is_base_of_v<BaseManager, DerivedManager>)
         && (ConstructibleWith<DerivedManager, Args...>)
            template <typename... CallArgs>
                requires(IsSupportedArg<CallArgs, Args...> && ...)
std::shared_ptr<DerivedManager> ManagerCreator<BaseManager, DerivedManager, Args...>::getInstance(
    CallArgs &&...args)
{
    static std::shared_ptr<DerivedManager> m_instance;
    if (!m_instance)
        m_instance = std::make_shared<DerivedManager>(std::forward<CallArgs>(args)...);

    return m_instance;
}
