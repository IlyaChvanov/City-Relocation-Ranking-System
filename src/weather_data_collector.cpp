#include "weather_data_collector.h"

#include <string>
#include <iostream>


void WeatherDataCollector::FetchData(const std::string& city) {
  auto coord = CoordFromName(city);
  auto lat = std::to_string(coord.lat);
  auto lon = std::to_string(coord.lon);
  std::string host = "meteostat.p.rapidapi.com";
  std::string url = "https://meteostat.p.rapidapi.com/point/monthly?"
                    "lat=" + lat + "&lon=" + lon + "&alt=43&start=2020-01-01&end=2020-12-31";

  json_data_ = PerformGetRequest(host, url, rapid_api_key_);
}

std::pair<std::string, std::string> WeatherDataCollector::GetParsedData() {

}
void WeatherDataCollector::ParseData(const nlohmann::json& json) {

}

CityCoord WeatherDataCollector::CoordFromName(const std::string& city) {
  std::string url = "https://open-weather13.p.rapidapi.com/city/" + city + "/EN";
  std::string host = "open-weather13.p.rapidapi.com";
  auto json = PerformGetRequest(host, url, rapid_api_key_);
  double lat = json.at("coord").at("lat");
  double lon = json.at("coord").at("lon");
  return {lat, lon};
}
const nlohmann::json& WeatherDataCollector::GetJson() const {
  return json_data_;
}

std::ostream& operator<<(std::ostream& os, const CityCoord& coord) {
  os << "CityCoord(" << coord.lat << ", " << coord.lon << ")";
  return os;
}


