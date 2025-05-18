#include "LoadCommand.h"

CarcassLoadCommand::CarcassLoadCommand(InternalRepresentationId repr, const std::string &filename) :
    m_action(&LoadManager::load), m_repr(repr), m_filename(filename)
{ }

void CarcassLoadCommand::execute()
{
    ((*m_loadManager).*m_action)(m_repr, m_filename);
}
