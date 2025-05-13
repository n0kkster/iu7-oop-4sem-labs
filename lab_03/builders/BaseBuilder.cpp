#include "BaseBuilder.h"

BaseBuilder::BaseBuilder(std::shared_ptr<BaseReader> reader) : m_product(nullptr), m_reader(reader) { };

std::shared_ptr<BaseObject> BaseBuilder::getProduct()
{
    if (!m_product)
        m_product = createProduct();

    return m_product;
}
