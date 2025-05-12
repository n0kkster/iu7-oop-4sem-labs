#include "../../../component/primitive/visible/model/structure/BaseStructure.h"
#include "../BaseModelBuilder.h"
#include "../../../readers/model/carcass/CarcassReader.h"

#include <memory>

class CarcassModelBuilder : public BaseModelBuilder
{
private:
    std::shared_ptr<BaseStructure> m_structure;
    friend ModelReader;

public:
    CarcassModelBuilder() = delete;
    explicit CarcassModelBuilder(std::shared_ptr<CarcassReader> reader);

    virtual ~CarcassModelBuilder() override = default;

    bool buildVertices() override;
    bool buildEdges() override;
    bool buildCenter() override;

    std::shared_ptr<BaseObject> createProduct() override;
};
