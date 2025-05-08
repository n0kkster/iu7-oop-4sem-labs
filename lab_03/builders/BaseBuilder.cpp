#include "BaseBuilder.h"

BaseBuilder::BaseBuilder() : m_product(nullptr) { };

std::shared_ptr<BaseObject> BaseBuilder::getProduct()
{
    if (!m_product)
        m_product = createProduct();

    return m_product;
}
