#include "../BaseProjectionStrategy.h"

#include <vector>

class DefaultProjectionStrategy : public BaseProjectionStrategy
{
private:
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;

public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    void prepare(std::shared_ptr<const BaseModel> model, std::shared_ptr<const BaseCamera> camera,
                 const size_t width, const size_t height) override;
    const std::vector<Vertex> getVertices() const noexcept override;
    const std::vector<Edge> getEdges() const noexcept override;
};
