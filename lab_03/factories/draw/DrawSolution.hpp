#pragma once

#include "DrawSolution.h"

template <typename Tfactory, typename Tscene>
std::unique_ptr<BasePainter> DrawSolution::createPainter(std::shared_ptr<Tscene> scene)
{
    std::shared_ptr<BaseDrawFactory> factory = std::make_shared<Tfactory>(scene);

    return factory->createPainter();
}
