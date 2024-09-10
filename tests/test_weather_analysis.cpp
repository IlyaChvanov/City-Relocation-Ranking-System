#include "gtest/gtest.h"

#include "weather_analysis.h"
#include "weather_data_collector.h"

nlohmann::json CreateTestDataGood() {
  nlohmann::json data;
  for (int i = 1; i <= 12; ++i) {
    data["data"].push_back({{"tavg", static_cast<double>(i)}});
  }
  return data;
}

nlohmann::json CreateTestDataEmpty() {
  return nlohmann::json{};
}

TEST(WeatherAnalysis, AnalyseGood) {
  auto json = CreateTestDataGood();
  WeatherAnalysis w;
  w.Analyse(json);
  EXPECT_EQ(w.GetAvgTemp(), 6.5);
}

TEST(WeatherAnalysis, AnalyseEmpty) {
  auto json = CreateTestDataEmpty();
  WeatherAnalysis w;
  EXPECT_THROW(w.Analyse(json), EmptyJson);
}