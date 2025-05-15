#include "LoadManager.h"

#include "../../directors/model/carcass/CarcassDirector.h"
#include "../../ids/ids.h"
#include "../ManagerSolution.h"

#include <memory>

LoadManager::LoadManager()
{
    m_directorSolution = std::make_shared<BaseDirectorSolution>();
    m_directorSolution->registrate<CarcassDirector, const std::string &, InternalRepresentationId>(DirectorId::CarcassDirectorId);
}

void LoadManager::load(DirectorId directorId, InternalRepresentationId repr,
                       const std::string &filename)
{
    auto director = m_directorSolution->create(directorId, filename, repr);

    auto object = director->create();

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->addObject(object);
}
