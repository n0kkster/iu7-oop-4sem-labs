#pragma once

#include "../BaseCarcassReadStrategy.h"
#include "../csv/CsvCarcassReadStrategy.h"
#include "../obj/ObjCarcassReadStrategy.h"
#include "../txt/TxtCarcassReadStrategy.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class CarcassReadStrategySolution
{
private:
    using StrategyMap = std::map<std::string, std::function<std::shared_ptr<BaseCarcassReadStrategy>(
                                                  std::shared_ptr<std::ifstream> &file)>>;

    StrategyMap m_map = {
        { ".txt",
         [](std::shared_ptr<std::ifstream> &file) {
         return std::make_shared<TxtCarcassReadStrategy>(file);
         } },
        { ".csv",
         [](std::shared_ptr<std::ifstream> &file) {
         return std::make_shared<CsvCarcassReadStrategy>(file);
         } },
        { ".obj",
         [](std::shared_ptr<std::ifstream> &file) {
         return std::make_shared<ObjCarcassReadStrategy>(file);
         } },
    };

public:
    CarcassReadStrategySolution() = default;
    ~CarcassReadStrategySolution() = default;

    std::shared_ptr<BaseCarcassReadStrategy> create(const std::string &filename,
                                                    std::shared_ptr<std::ifstream> file);
};
