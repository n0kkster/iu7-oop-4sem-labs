#include "CarcassReadStrategySolution.h"
#include "../../../exceptions/model/carcass/CarcassException.h"
#include <filesystem>

std::shared_ptr<BaseCarcassReadStrategy> CarcassReadStrategySolution::create(
    const std::string &filename, std::shared_ptr<std::ifstream> file)
{
    std::string extension = std::filesystem::path(filename).extension();
    if (auto it = m_map.find(extension); it != m_map.end())
        return it->second(file);

    throw CarcassInvalidFileFormat("Unsupported file extension!");
}
