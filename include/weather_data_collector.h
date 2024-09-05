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
  std::pair<std::string, std::string> GetParsedData() override;
  CityCoord CoordFromName(const std::string& city);
  const nlohmann::json& GetJson() const;
 private:
  void ParseData(const nlohmann::json& json) override;
  std::pair<std::string, std::string> parsed_data_;
  nlohmann::json json_data_;
  const std::string open_weather_api_key_ = "e11afd83108e17017c5e0d702da57366"; // for getting coordinates of city
  const std::string meteostat_api_key_ = "09f92165camsh8fa691b469e8ed0p134d18jsn96645ff43329"; // for getting weather
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_
