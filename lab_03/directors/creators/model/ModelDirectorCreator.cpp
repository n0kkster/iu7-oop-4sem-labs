#include "ModelDirectorCreator.h"
#include "../../model/ModelDirector.h"

std::shared_ptr<BaseDirector> ModelDirectorCreator::create(std::shared_ptr<BaseBuilder> builder)
{
    return std::make_shared<ModelDirector>(builder);
}
