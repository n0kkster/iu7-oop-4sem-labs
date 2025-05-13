#include "../../../component/primitive/visible/model/structure/BaseStructure.h"
#include "../../../component/primitive/visible/model/structure/list/ListStructure.h"
#include "../../../component/primitive/visible/model/structure/matrix/MatrixStructure.h"
#include "../../../ids/ids.h"
#include "../../../readers/model/carcass/CarcassReader.h"
#include "../BaseModelBuilder.h"

#include <functional>
#include <map>
#include <memory>

class CarcassModelBuilder : public BaseModelBuilder
{
public:
    using RepresentationMap =
        std::map<InternalRepresentation, std::function<std::shared_ptr<BaseStructure>()>>;

private:
    std::shared_ptr<BaseStructure> m_structure;
    const RepresentationMap m_reprMap = 
    {
        {InternalRepresentation::ListInternalReprsentationId, [](){return std::make_shared<ListStructure>();}},
        // {InternalRepresentation::MatrixInternalReprsentationId, [](){return std::make_shared<MatrixStructure>();}}
    };
    friend ModelReader;

public:
    CarcassModelBuilder() = delete;
    CarcassModelBuilder(std::shared_ptr<BaseReader> reader, InternalRepresentation repr);

    virtual ~CarcassModelBuilder() override = default;

    bool buildVertices() override;
    bool buildEdges() override;
    bool buildCenter() override;

    std::shared_ptr<BaseObject> createProduct() override;
};
