#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_

#include "i_data_collector.h"
#include <nlohmann/json.hpp>
#include <string>

struct CityCoord {
  double lat;
  double lon;
};

class WeatherDataCollector : public IDataCollector {
 public:
  void FetchData(const std::string& city) override;
  CityCoord CoordFromName(const std::string& city);
  const nlohmann::json& GetJson() const;
 private:
  std::pair<std::string, std::string> parsed_data_;
  nlohmann::json json_data_;
  const std::string rapid_api_key_ = "6c68e5896fmsh46989a323b71aa9p1e1246jsna881987f1a3a";
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_
