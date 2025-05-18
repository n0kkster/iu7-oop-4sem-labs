#include "DrawManager.h"

#include "../../strategies/ConvertCoordinates/creator/ConvertCoordsStrategyCreator.h"
#include "../../strategies/HiddenEdgesRemoval/creator/HiddenEdgeRemovalStrategyCreator.h"
#include "../../strategies/projection/creators/ProjectionStrategyCreator.h"
#include "../../visitors/creators/VisitorCreator.h"
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

    auto projStrategy = DefaultProjectionStrategyCreator::create();
    auto removalStrategy = RaycastingHiddenEdgeRemovalStrategyCreator::create();
    auto convertStrategy = DefaultConvertCoordinatesStrategyCreator::create();

    auto drawVisitor = DrawVisitorCreator::create(std::move(projStrategy), std::move(removalStrategy),
                                                  std::move(convertStrategy), m_painter, activeCam);

    auto sceneManager = ManagerSolution::getSceneManager();
    sceneManager->accept(drawVisitor);
}
