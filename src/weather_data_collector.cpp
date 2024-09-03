#include "weather_data_collector.h"

#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void WeatherDataCollector::FetchData(const std::string& city) {
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
std::ostream& operator<<(std::ostream& os, const CityCoord& coord) {
  os << "CityCoord(" << coord.lat << ", " << coord.lon << ")";
  return os;
}


