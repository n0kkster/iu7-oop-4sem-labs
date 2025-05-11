#include "../DirectorCreator.h"

class ModelDirectorCreator : public BaseDirectorCreator
{
public:
    ModelDirectorCreator() = default;
    virtual ~ModelDirectorCreator() override = default;

    std::shared_ptr<BaseDirector> create(std::shared_ptr<BaseBuilder> builder) override;
};