#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_

class WeatherDataCollector {

struct CityCoord {
  friend std::ostream& operator<<(std::ostream& os, const CityCoord& coord);
  double lat;
  double lon;
};


class WeatherDataCollector : public IDataCollector {
 public:
  void FetchData(const std::string& city) override;
  std::pair<std::string, std::string> GetParsedData() override;
  CityCoord CoordFromName(const std::string& city);
 private:
  void ParseData(const nlohmann::json& json) override;
  std::pair<std::string, std::string> parsed_data_;
  const std::string open_weather_api_key_ = "457b2a41705a1c5415360df4a71b8d59";
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_DATA_COLLECTOR_H_
