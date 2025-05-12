#pragma once

#include "../../directors/DirectorSolution.h"
#include "../../readers/ReaderSolution.h"
#include "../BaseManager.h"

#include <cstddef>
#include <memory>
#include <string>

class LoadManager : public BaseManager
{
private:
    std::shared_ptr<ReaderSolution> m_readerSolution;
    std::shared_ptr<BaseDirectorSolution> m_directorSolution;

public:
    LoadManager();
    virtual ~LoadManager() override = default;

    std::shared_ptr<BaseObject> load(ReaderIds readerId, DirectorIds directorId, InternalRepresentation repr, const std::string &filename);
};
