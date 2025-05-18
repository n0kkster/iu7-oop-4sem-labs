#pragma once

#include "../../component/primitive/visible/model/structure/BaseStructure.h"
#include "../../component/primitive/visible/model/structure/list/ListStructure.h"
#include "../../component/primitive/visible/model/structure/matrix/MatrixStructure.h"
#include "../../ids/ids.h"
#include "../../reader/ModelReader.h"
#include "../BaseBuilder.h"

#include <functional>
#include <map>

class BuilderSolution
{
private:
    using ModelRepresentationMap =
        std::map<InternalRepresentationId, std::function<std::shared_ptr<BaseStructure>()>>;

    const ModelRepresentationMap m_reprMap = {
        {   InternalRepresentationId::ListInternalReprsentationId,
         []() {
         return std::make_shared<ListStructure>();
         } },
        { InternalRepresentationId::MatrixInternalReprsentationId,
         []() {
         return std::make_shared<MatrixStructure>();
         } }
    };

public:
    BuilderSolution() = default;
    ~BuilderSolution() = default;
    
    std::shared_ptr<BaseBuilder> create(std::shared_ptr<ModelReader> reader, InternalRepresentationId repr);
};
