#include "ReaderSolution.h"

#include "../../exceptions/model/ModelException.h"
#include "../creator/ReaderCreator.h"

#include <filesystem>

std::shared_ptr<ModelReader> ReaderSolution::create(const std::string &filename)
{
    std::string extension = std::filesystem::path(filename).extension().string();
    auto it = m_map.find(extension);

    if (it == m_map.end())
        ModelInvalidFileFormat("Unsupported file extension!");

    auto impl = it->second(filename);
    return ModelReaderCreator::create(impl);
}
