#include "CameraFactory.h"
#include "../../exceptions/camera/CameraException.h"

std::shared_ptr<BaseCamera> CameraFactory::create(const CameraId &id)
{
    if (auto it = m_map.find(id); it != m_map.end())
        return it->second();

    throw UnknownCameraException("Invalid camera id!");
}
