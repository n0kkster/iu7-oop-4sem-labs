#pragma once

#include "DrawSolution.h"

template <typename Tfactory, typename Tscene>
std::unique_ptr<BasePainter> DrawerSolution<Tfactory, Tscene>::createPainter(std::unique_ptr<Tscene> scene)
{
    std::shared_ptr<BaseDrawFactory> factory = std::make_shared<Tfactory>(std::move(scene));

    return factory->createPainter();
}
