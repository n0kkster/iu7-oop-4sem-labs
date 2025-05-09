#include "../../products/BaseScene.h"

#include <memory>
#include <QGraphicsScene>

class QtScene : public BaseScene
{
private:
    std::shared_ptr<QGraphicsScene> m_scene;

public:
    QtScene() = delete;
    explicit QtScene(std::shared_ptr<QGraphicsScene> scene);

    virtual ~QtScene() override = default;

    void addLine(const Vertex &p1, const Vertex &p2) override;
    void addLine(const double x1, const double y1, const double x2, const double y2) override;

    void clear() override;
};
