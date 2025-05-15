#pragma once

#include "../../directors/DirectorSolution.h"
#include "../BaseManager.h"

#include <cstddef>
#include <memory>
#include <string>

class LoadManager : public BaseManager
{
private:
    std::shared_ptr<BaseDirectorSolution> m_directorSolution;

public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void load(DirectorId directorId, InternalRepresentationId repr, const std::string &filename);
};
