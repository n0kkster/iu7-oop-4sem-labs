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
    m_readerSolution = std::make_shared<BaseReaderSolution>();

    m_directorSolution
        ->template registrate<CarcassDirector, std::shared_ptr<CarcassReader>, InternalRepresentation>(
            DirectorIds::CarcassDirectorId);

    m_readerSolution->registrate<TxtCarcassReader, const std::string &>(ReaderIds::CarcassTxtReaderId);
    m_readerSolution->registrate<ObjCarcassReader, const std::string &>(ReaderIds::CarcassObjReaderId);
    m_readerSolution->registrate<CsvCarcassReader, const std::string &>(ReaderIds::CarcassCsvReaderId);
}

std::shared_ptr<BaseObject> LoadManager::load(ReaderIds readerId, DirectorIds directorId,
                                              InternalRepresentation repr, const std::string &filename)
{
    auto reader = m_readerSolution->create(readerId, filename);
    auto director = m_directorSolution->create(directorId, reader, repr);

    return director->create();
}
