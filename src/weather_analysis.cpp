#include "weather_analysis.h"

void WeatherAnalysis::ParseJson(const nlohmann::json& data) {
  if (!data.contains("data")) {
    throw EmptyJson("No Data");
  }
  std::transform(data.at("data").begin(), data.at("data").end(),
                 std::back_inserter(temperatures_),
                 [](const auto& el) { return el.at("tavg"); });

}
void WeatherAnalysis::Analyse(const nlohmann::json& data) {
  ParseJson(data);
  avg_temp_ = std::accumulate(temperatures_.begin(), temperatures_.end(), 0.0) / 12;
  if (abs(best_temp - avg_temp_) > 2.5) {
    points_ = 0;
  } else {
    points_ = 10;
  }
}
double WeatherAnalysis::GetPoints() const {
  return points_;
}
double WeatherAnalysis::GetAvgTemp() const {
  return avg_temp_;
}
