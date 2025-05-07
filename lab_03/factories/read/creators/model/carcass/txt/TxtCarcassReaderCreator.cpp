#include "TxtCarcassReaderCreator.h"

#include "../../../../../../readers/model/carcass/txt/TxtCarcassReader.h"

std::shared_ptr<BaseReader> TxtCarcassReaderCreator::create(const std::string &filename)
{
    return std::make_shared<TxtCarcassReader>(filename);
}
