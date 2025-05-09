#include "RotateVisitor.h"

#include "../../../transformations/actions/rotate/RotateAction.h"

RotateVisitor::RotateVisitor(const RotationParams &params) :
    TransformVisitor(std::make_shared<RotateAction>(params))
{ }
