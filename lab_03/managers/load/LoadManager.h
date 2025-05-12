#pragma once

#include "../../directors/DirectorSolution.h"
#include "../../factories/read/ReaderSolution.h"
#include "../BaseManager.h"

#include <cstddef>
#include <memory>
#include <string>

class LoadManager : public BaseManager
{
private:
    std::shared_ptr<ReaderSolution> m_readerSolution;
    std::shared_ptr<DirectorSolution> m_directorSolution;

public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void load(size_t readerId, size_t directorId, const std::string &filename);
};
