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
    m_directorSolution = std::make_shared<BaseDirectorSolution>();
    m_readerSolution = std::make_shared<ReaderSolution>();

    m_directorSolution
        ->template registrate<CarcassDirector, std::shared_ptr<CarcassReader>, InternalRepresentation>(
            DirectorIds::CarcassDirectorId);


    m_readerSolution->registrate(CarcassTxtReaderId,
                                 ReaderCreatorMaker::createReaderCreator<TxtCarcassReader>);
    m_readerSolution->registrate(CarcassObjReaderId,
                                 ReaderCreatorMaker::createReaderCreator<ObjCarcassReader>);
    m_readerSolution->registrate(CarcassCsvReaderId,
                                 ReaderCreatorMaker::createReaderCreator<CsvCarcassReader>);
}

std::shared_ptr<BaseObject> LoadManager::load(ReaderIds readerId, DirectorIds directorId,
                                              InternalRepresentation repr, const std::string &filename)
{
    std::shared_ptr<BaseReaderCreator> readerCreator = m_readerSolution->create(readerId);

    auto reader = readerCreator->create(filename);
    auto director = m_directorSolution->create(directorId, reader, repr);

    return director->create();
}
