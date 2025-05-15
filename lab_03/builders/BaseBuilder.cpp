#include "BaseBuilder.h"

std::shared_ptr<BaseObject> BaseBuilder::getProduct()
{
    if (!m_product)
        m_product = createProduct();

    return m_product;
}
