#include "../BaseProjectionStrategy.h"

#include <vector>

class DefaultProjectionStrategy : public BaseProjectionStrategy
{
public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    void project(std::shared_ptr<const BaseStructure> structure, std::shared_ptr<const BaseCamera> camera,
                 std::vector<Vertex> &projected) override;
};
