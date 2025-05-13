#include "CameraFactory.h"
#include <stdexcept>

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraIds &id)
{
    auto it = m_map.find(id);
    if (it == m_map.end())
        throw std::runtime_error("Invalid camera id!");
    return it->second();
}
