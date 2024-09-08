#include "weather_data_collector.h"

#include <string>
#include <iostream>


void WeatherDataCollector::FetchData(const std::string& city) {
  try {
    auto coord = CoordFromName(city);
    auto lat = std::to_string(coord.lat);
    auto lon = std::to_string(coord.lon);
    std::string host = "meteostat.p.rapidapi.com";
    std::string url = "https://meteostat.p.rapidapi.com/point/monthly?"
                      "lat=" + lat + "&lon=" + lon + "&alt=43&start=2020-01-01&end=2020-12-31";
    json_data_ = PerformGetRequest(host, url, rapid_api_key_);
  } catch (const ErrorConnect& e) {
    std::cerr << e.what();
    throw;
  }
}

CityCoord WeatherDataCollector::CoordFromName(const std::string& city) {
  std::string url = "https://open-weather13.p.rapidapi.com/city/" + city + "/EN";
  std::string host = "open-weather13.p.rapidapi.com";
  auto json = PerformGetRequest(host, url, rapid_api_key_);
  std::cout << json.dump(4);
  if (json.contains("message")) {
    if (json.at("message") == "You have exceeded the MONTHLY quota for Requests on your current plan, BASIC. Upgrade your plan at https\n"
                              "://rapidapi.com/worldapi/api/open-weather13") {
      throw ErrorConnect("You have exceeded the MONTHLY quota for Requests");
    } else if (json.at("message") == "Not found") {
      throw ErrorConnect("Incorrect city name");
    }
  }
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


