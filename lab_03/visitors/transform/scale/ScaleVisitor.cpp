#include "ScaleVisitor.h"

#include "../../../transformations/actions/scale/ScaleAction.h"

ScaleVisitor::ScaleVisitor(const ScaleParams &params) :
    TransformVisitor(std::make_shared<ScaleAction>(params))
{ }
