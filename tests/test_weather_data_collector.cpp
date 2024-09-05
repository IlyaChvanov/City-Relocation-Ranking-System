#include "gtest/gtest.h"

#include "weather_data_collector.h"

struct WeatherDataCollectorTest : public testing::Test {
  WeatherDataCollector* w;
  CityCoord* london;
  void SetUp() override {
    w = new WeatherDataCollector();
    london = new CityCoord (51.5073, -0.127647);
  }
  void TearDown() override {
    delete w;
    delete london;
  }
};

TEST_F(WeatherDataCollectorTest, CoordFromName) {
  CityCoord result = w->CoordFromName("London");

  const double epsilon = 1e-1; // epsilon = 1e-1: это примерно 11
  // км (этого обычно достаточно для идентификации одного города)

  ASSERT_NEAR(london->lat, result.lat, epsilon);
  ASSERT_NEAR(london->lon, result.lon, epsilon);
}

TEST_F(WeatherDataCollectorTest, FetchData) {
  // Создаем корректные данные
  nlohmann::json correct;
  correct["data"] = {
      {
          {"date", "2020-01-01"},
          {"tavg", 4.7},
          {"tmin", 1.8},
          {"tmax", 7.3},
          {"prcp", 34.0},
          {"wspd", 13.2},
          {"pres", 1021.4},
          {"tsun", 3660}
      }
  };

  w->FetchData("London");
  nlohmann::json result = w->GetJson();

  ASSERT_TRUE(result.contains("data")) << "The JSON response does not contain 'data' field.";
  ASSERT_EQ(correct["data"][0], result["data"][0]) << "The fetched data does not match the expected data.";
}