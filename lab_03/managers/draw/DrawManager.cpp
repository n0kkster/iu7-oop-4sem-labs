#include "DrawManager.h"

#include "../../strategies/projection/creators/DefaultProjectionStrategyCreator.h"
#include "../../visitors/creators/ConcreteVisitorCreator.h"
#include "../ManagerSolution.h"

#include <iostream>

void DrawManager::setPainter(std::shared_ptr<BasePainter> painter)
{
    std::cout << "setPainter(): this: " << this << " passed painter: " << painter << std::endl;
    m_painter = painter;
    std::cout << "m_painter: " << m_painter << std::endl;
}

void DrawManager::draw()
{
    std::cout << "draw(): this: " << this << std::endl;
    std::cout << "m_painter: " << m_painter << std::endl;
    m_painter->clear();

    auto cameraManager = ManagerSolution::getCameraManager();

    std::cout << "camera manager: " << cameraManager << std::endl;

    auto activeCam = cameraManager->getActiveCamera();

    std::cout << "active cam: " << activeCam << std::endl;

    DefaultProjectionStrategyCreator stratCreator;
    auto strategy = stratCreator.create();

    DrawVisitorCreator creator;
    auto drawVisitor = creator.create(std::move(strategy), m_painter, activeCam);

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->accept(drawVisitor);
}
