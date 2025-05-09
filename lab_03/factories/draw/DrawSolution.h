#pragma once

#include "BaseDrawFactory.h"
#include "products/BasePainter.h"
#include "qt/QtDrawFactory.h"

#include <memory>

template <typename Tfactory, typename Tscene>
class DrawerSolution
{
public:
    std::unique_ptr<BasePainter> createPainter(std::unique_ptr<Tscene> scene);
};

#include "DrawSolution.hpp"
