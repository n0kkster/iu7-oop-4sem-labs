#include "DefaultProjectionStrategy.h"

void DefaultProjectionStrategy::project(std::shared_ptr<const BaseStructure> structure,
                                        std::shared_ptr<const BaseCamera> camera, std::vector<Vertex> &projected)
{
    projected.clear();

    const auto &vertices = structure->getVertices();
    const auto &edges = structure->getEdges();
    const auto &lookMatrix = camera->getLookMatrix();
    const auto &projectionMatrix = camera->getProjectionMatrix(1.0);
    const auto transformMatrix = projectionMatrix * lookMatrix;

    for (const Vertex &v : vertices)
    {
        Vertex proj(v);
        proj.transform(transformMatrix);

        double w = proj.getW();
        if (w != 0.0)
        {
            proj.setX(proj.getX() / w);
            proj.setY(proj.getY() / w);
            proj.setZ(proj.getZ() / w);
        }

        projected.push_back(proj);
    }
}
