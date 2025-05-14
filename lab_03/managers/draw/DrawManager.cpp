#include "DrawManager.h"

#include "../../strategies/projection/creators/DefaultProjectionStrategyCreator.h"
#include "../../visitors/creators/ConcreteVisitorCreator.h"
#include "../ManagerSolution.h"

void DrawManager::setPainter(std::shared_ptr<BasePainter> painter)
{
    m_painter = painter;
}

void DrawManager::draw()
{
    m_painter->clear();

    auto cameraManager = ManagerSolution::getCameraManager();

    auto activeCam = cameraManager->getActiveCamera();

    DefaultProjectionStrategyCreator stratCreator;
    auto strategy = stratCreator.create();

    DrawVisitorCreator creator;
    auto drawVisitor = creator.create(std::move(strategy), m_painter, activeCam);

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->accept(drawVisitor);
}
