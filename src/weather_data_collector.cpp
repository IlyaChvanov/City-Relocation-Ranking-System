#include "weather_data_collector.h"

#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void WeatherDataCollector::FetchData(const std::string& city) {
  auto coord = CoordFromName(city);
  auto lat = std::to_string(coord.lat);
  auto lon = std::to_string(coord.lon);
  std::string host = "api.meteostat.net";
  std::string target = "/point/monthly?lat= "+ lat + "&lon=" + lon +
      "&alt=43&start=2020-01-01&end=2020-12-31";

  json_data_ = PerformGetRequest(host, target, meteostat_api_key_);
}

std::pair<std::string, std::string> WeatherDataCollector::GetParsedData() {

}
void WeatherDataCollector::ParseData(const nlohmann::json& json) {

}

CityCoord WeatherDataCollector::CoordFromName(const std::string& city) {
  std::string host = "api.openweathermap.org";
  std::string target = "/geo/1.0/direct?q=" + city +
                       "&limit=1&appid=" + open_weather_api_key_;
  auto json = PerformGetRequest(host, target);
  double lat = json[0].at("lat");
  double lon = json[0].at("lon");
  return {lat, lon};
}
const nlohmann::json& WeatherDataCollector::GetJson() const {
  return json_data_;
}

std::ostream& operator<<(std::ostream& os, const CityCoord& coord) {
  os << "CityCoord(" << coord.lat << ", " << coord.lon << ")";
  return os;
}


