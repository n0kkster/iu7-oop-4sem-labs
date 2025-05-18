#include "LoadManager.h"

#include "../../ids/ids.h"
#include "../ManagerSolution.h"

LoadManager::LoadManager()
{
    m_dsol = std::make_shared<BaseDirectorSolution>();
    m_dsol->registrate<CarcassDirector, std::shared_ptr<BaseBuilder>>(
        DirectorId::CarcassDirectorId);
}

void LoadManager::load(InternalRepresentationId repr, const std::string &filename)
{
    ReaderSolution rsol;
    auto reader = rsol.create(filename);

    BuilderSolution bsol;
    auto builder = bsol.create(reader, repr);

    auto director = m_dsol->create(DirectorId::CarcassDirectorId, builder);

    auto object = director->create();

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->addObject(object);
}
