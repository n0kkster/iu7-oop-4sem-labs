#pragma once

#include "BaseDrawFactory.h"
#include "products/BasePainter.h"
#include "qt/QtDrawFactory.h"

#include <memory>

class DrawSolution
{
public:
    template <typename Tfactory, typename Tscene>
    static std::unique_ptr<BasePainter> createPainter(std::shared_ptr<Tscene> scene);
};

#include "DrawSolution.hpp"
