#include "LoadCommand.h"

#include "../../managers/ManagerSolution.h"

CarcassLoadCommand::CarcassLoadCommand(InternalRepresentationId repr, const std::string &filename) :
    m_action(&LoadManager::load), m_repr(repr), m_filename(filename),
    m_loadManager(ManagerSolution::getLoadManager())
{ }

void CarcassLoadCommand::execute()
{
    ((*m_loadManager).*m_action)(m_repr, m_filename);
}
