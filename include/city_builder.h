#ifndef CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_
#define CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_

#include "City.h"
#include "nlohmann/json.hpp"
#include "memory"

using Json = nlohmann::json;
class CityBuilder {
 public:
  std::unique_ptr<const City> Build(const std::string city_name);
 private:
  Json CollectWeather();
  Json CollectLanguage();
  Json CollectLifeQuality();
  void SetWeatherP(const Json& weather);
  void SetLanguageP(const Json& language);
  void SetLifeQualityP(const Json& life_quality);
  City city_;
};

#endif //CITY_RELOCATION_RANKING_SYSTEM_SRC_CITYBUILDER_H_
