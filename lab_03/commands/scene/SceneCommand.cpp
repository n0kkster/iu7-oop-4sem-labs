#include "SceneCommand.h"

#include "../../managers/ManagerSolution.h"

DrawSceneCommand::DrawSceneCommand() :
    m_method(&DrawManager::draw), m_drawManager(ManagerSolution::getDrawManager())
{ }

void DrawSceneCommand::execute()
{
    ((*m_drawManager).*m_method)();
}
