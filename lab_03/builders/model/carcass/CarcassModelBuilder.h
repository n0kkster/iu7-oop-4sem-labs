#include "../../../component/primitive/visible/model/carcass/structure/BaseStructure.h"
#include "../BaseModelBuilder.h"
#include "../../../readers/model/ModelReader.h"

#include <memory>

class CarcassModelBuilder : public BaseModelBuilder
{
private:
    std::shared_ptr<BaseStructure> m_structure;
    friend ModelReader;

public:
    CarcassModelBuilder() = delete;
    explicit CarcassModelBuilder(std::shared_ptr<ModelReader> reader);

    virtual ~CarcassModelBuilder() override = default;

    bool buildVertices() override;
    bool buildEdges() override;
    bool buildCenter() override;

    std::shared_ptr<BaseObject> createProduct() override;
};
