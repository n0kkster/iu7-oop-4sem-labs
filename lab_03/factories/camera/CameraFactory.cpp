#include "CameraFactory.h"
#include <stdexcept>

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraId &id)
{
    if (auto it = m_map.find(id); it != m_map.end())
        return it->second();

    throw std::runtime_error("Invalid camera id!");
}
