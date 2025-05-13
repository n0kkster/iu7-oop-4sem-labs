#include "DrawManager.h"
#include "../ManagerSolution.h"

void DrawManager::setPainter(std::unique_ptr<BasePainter> painter)
{
    m_painter = std::move(painter);
}

void DrawManager::draw()
{
    m_painter->clear();

    auto sceneManager = ManagerSolution::getSceneManager();
}
