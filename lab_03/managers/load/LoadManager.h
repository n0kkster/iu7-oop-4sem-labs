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
    std::shared_ptr<BaseReaderSolution> m_readerSolution;
    std::shared_ptr<BaseDirectorSolution> m_directorSolution;

public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void load(ReaderId readerId, DirectorId directorId, InternalRepresentationId repr, const std::string &filename);
};
