#include "LoadManager.h"

#include "../../ids/ids.h"

#include <memory>

LoadManager::LoadManager()
{
    m_directorSolution = std::make_shared<DirectorSolution>();
    m_readerSolution = std::make_shared<ReaderSolution>();

    m_directorSolution->registrate(
        DirectorIds::CarcassDirectorId,
        DirectorCreatorMaker::createDirectorCreator<CarcassDirector, std::shared_ptr<CarcassReader>>);

}
