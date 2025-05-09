#ifndef CONCRETE_VISITOR_CREATOR
#define CONCRETE_VISITOR_CREATOR

#include "../transform/move/MoveVisitor.h"
#include "../transform/rotate/RotateVisitor.h"
#include "../transform/scale/ScaleVisitor.h"
#include "../draw/DrawVisitor.h"
#include "BaseVisitorCreator.h"


template <typename Derived, typename Base>
concept Derivative = std::is_base_of_v<Base, Derived>;

template <typename T, typename... Args>
concept ConstructibleWith = requires(Args &&...args) { T{ std::forward<Args>(args)... }; };


template <typename BaseVisitor, typename DerivedVisitor, typename... Args>
    requires Derivative<DerivedVisitor, BaseVisitor> && ConstructibleWith<DerivedVisitor, Args...>
class ConcreteVisitorCreator : public BaseVisitorCreator<BaseVisitor, Args...>
{
public:
    ConcreteVisitorCreator() = default;
    ~ConcreteVisitorCreator() = default;

    std::shared_ptr<BaseVisitor> create(Args &&...args) override;
};

#include "ConcreteVisitorCreator.hpp"

using RotateVisitorCreator = ConcreteVisitorCreator<TransformVisitor, RotateVisitor, RotationParams>;

using TransponseVisitorCreator = ConcreteVisitorCreator<TransformVisitor, MoveVisitor, MoveParams>;

using ScaleVisitorCreator = ConcreteVisitorCreator<TransformVisitor, ScaleVisitor, ScaleParams>;

// using DrawVisitorCreator = ConcreteVisitorCreator<BaseVisitor, DrawVisitor, std::shared_ptr<BaseDrawer>,
//                                                   std::shared_ptr<BaseCamera>>;

#endif
