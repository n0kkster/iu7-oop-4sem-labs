#include "LoadManager.h"

#include "../../directors/model/carcass/CarcassDirector.h"
#include "../../ids/ids.h"
#include "../../readers/model/carcass/csv/CsvCarcassReader.h"
#include "../../readers/model/carcass/obj/ObjCarcassReader.h"
#include "../../readers/model/carcass/txt/TxtCarcassReader.h"
// #include "../../directors/camera/

#include <memory>

LoadManager::LoadManager()
{
    m_directorSolution = std::make_shared<DirectorSolution>();
    m_readerSolution = std::make_shared<ReaderSolution>();

    m_directorSolution->registrate(DirectorIds::CarcassDirectorId,
                                   DirectorCreatorMaker::createDirectorCreator<CarcassDirector>);
    // m_directorSolution->registrate(
    // DirectorIds::CarcassDirectorId,
    // DirectorCreatorMaker::createDirectorCreator<CameraDirector, std::shared_ptr<CameraReader>>);

    m_readerSolution->registrate(CarcassTxtReaderId,
                                 ReaderCreatorMaker::createReaderCreator<TxtCarcassReader>);
    m_readerSolution->registrate(CarcassObjReaderId,
                                 ReaderCreatorMaker::createReaderCreator<ObjCarcassReader>);
    m_readerSolution->registrate(CarcassCsvReaderId,
                                 ReaderCreatorMaker::createReaderCreator<CsvCarcassReader>);
}

std::shared_ptr<BaseObject> LoadManager::load(size_t readerId, size_t directorId, const std::string &filename)
{
    std::shared_ptr<BaseDirectorCreator> directorCreator = m_directorSolution->create(directorId);
    std::shared_ptr<BaseReaderCreator> readerCreator = m_readerSolution->create(readerId);

    std::shared_ptr<BaseReader> reader = readerCreator->create(filename);
    std::shared_ptr<BaseDirector> director = directorCreator->create(reader);

    return director->create();
}
