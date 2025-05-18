#pragma once

#include "../../builders/solution/BuilderSolution.h"
#include "../../directors/DirectorSolution.h"
#include "../../reader/solution/ReaderSolution.h"
#include "../../directors/model/carcass/CarcassDirector.h"
#include "../BaseManager.h"

#include <cstddef>
#include <memory>
#include <string>

class LoadManager : public BaseManager
{
private:
    std::shared_ptr<BaseDirectorSolution> m_dsol;

public:
    LoadManager();
    virtual ~LoadManager() override = default;

    void load(InternalRepresentationId repr, const std::string &filename);
};
