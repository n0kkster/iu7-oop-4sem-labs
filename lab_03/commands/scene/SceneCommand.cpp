#include "SceneCommand.h"

DrawSceneCommand::DrawSceneCommand() : m_method(&DrawManager::draw) { }

void DrawSceneCommand::execute()
{
    ((*m_drawManager).*m_method)();
}
