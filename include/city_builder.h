#ifndef CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_
#define CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_

#include "City.h"
#include "nlohmann/json.hpp"
#include "memory"

using Json = nlohmann::json;
class CityBuilder {
 public:
  std::unique_ptr<const City> Build(const std::string& city_name,
                                    const std::string& country_name);
 private:
  double CollectWeatherPoints() const;
  double CollectLanguagePoints() const;
  double CollectLifeQualityPoints() const;
  double CountCommonPoints() const;
  City city_;
};

#endif //CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_
