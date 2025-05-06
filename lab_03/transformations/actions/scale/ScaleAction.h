#ifndef SCALEACTION_H
#define SCALEACTION_H

#include "../../params/scale/ScaleParams.h"
#include "../TransformAction.h"

class ScaleAction : public TransformAction
{
public:
    ScaleAction() = default;
    ~ScaleAction() override = default;

    ScaleAction(const ScaleParams &params);
    ScaleAction(const double k);

    ScaleAction(const Vertex &vertex, const ScaleParams &params);
    ScaleAction(const Vertex &vertex, const double k);

    bool isMoveAction() const noexcept override;
};

#endif /* SCALEACTION_H */
