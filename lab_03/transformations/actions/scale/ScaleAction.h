#ifndef SCALEACTION_H
#define SCALEACTION_H

#include "../../params/scale/ScaleParams.h"
#include "../TransformAction.h"

class ScaleAction : public TransformAction
{
public:
    ScaleAction() = default;
    virtual ~ScaleAction() override = default;

    ScaleAction(const ScaleParams &params);
    
    bool isMoveAction() const noexcept override;
};

#endif /* SCALEACTION_H */
