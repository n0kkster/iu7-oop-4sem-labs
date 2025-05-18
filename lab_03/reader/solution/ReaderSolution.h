#pragma once

#include "../impl/BaseModelReaderImpl.h"
#include "../impl/creator/ModelReaderImplCreator.h"
#include "../impl/csv/CsvModelReaderImpl.h"
#include "../impl/obj/ObjModelReaderImpl.h"
#include "../impl/txt/TxtModelReaderImpl.h"
#include "../ModelReader.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class ReaderSolution
{
private:
    using ImplMap =
        std::map<std::string,
                 std::function<std::shared_ptr<BaseModelReaderImpl>(const std::string &filename)>>;

    const ImplMap m_map = {
        { ".txt",
         [](const std::string &filename) {
         return TxtModelReaderImplCreator::create(filename);
         } },
        { ".csv",
         [](const std::string &filename) {
         return CsvModelReaderImplCreator::create(filename);
         } },
        { ".obj",
         [](const std::string &filename) {
         return ObjModelReaderImplCreator::create(filename);
         } },
    };

public:
    ReaderSolution() = default;
    ~ReaderSolution() = default;

    std::shared_ptr<ModelReader> create(const std::string &filename);
};
