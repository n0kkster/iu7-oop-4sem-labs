#include "LoadManager.h"

#include "../../directors/model/carcass/CarcassDirector.h"
#include "../../ids/ids.h"
#include "../../readers/model/carcass/CarcassReader.h"
#include "../ManagerSolution.h"

#include <memory>

LoadManager::LoadManager()
{
    m_directorSolution = std::make_shared<BaseDirectorSolution>();
    m_readerSolution = std::make_shared<BaseReaderSolution>();

    m_directorSolution->registrate<CarcassDirector, std::shared_ptr<CarcassReader>, InternalRepresentationId>(
        DirectorId::CarcassDirectorId);

    m_readerSolution->registrate<CarcassReader, const std::string &>(ReaderId::CarcassReaderId);
}

void LoadManager::load(ReaderId readerId, DirectorId directorId,
                                              InternalRepresentationId repr, const std::string &filename)
{
    auto reader = m_readerSolution->create(readerId, filename);
    auto director = m_directorSolution->create(directorId, reader, repr);

    auto object = director->create();

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->addObject(object);
}
