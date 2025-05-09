#include "MoveVisitor.h"

#include "../../../transformations/actions/move/MoveAction.h"

MoveVisitor::MoveVisitor(const MoveParams &params) :
    TransformVisitor(std::make_shared<MoveAction>(params))
{ }
