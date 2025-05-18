#include "../../../component/primitive/visible/model/structure/BaseStructure.h"
#include "../../../reader/ModelReader.h"
#include "../BaseModelBuilder.h"

#include <memory>

class CarcassModelBuilder : public BaseModelBuilder
{
private:
    std::shared_ptr<BaseStructure> m_structure;

public:
    CarcassModelBuilder() = delete;
    CarcassModelBuilder(std::shared_ptr<ModelReader> reader, std::shared_ptr<BaseStructure> structure);

    virtual ~CarcassModelBuilder() override = default;

    bool buildVertices() override;
    bool buildEdges() override;
    bool buildCenter() override;

    std::shared_ptr<BaseObject> createProduct() override;
};
