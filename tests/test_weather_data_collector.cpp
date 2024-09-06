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
  nlohmann::json correct;
  correct["data"] = {
      {
          {"date", "2020-01-01"},
          {"tavg", 7},
          {"tmin", 4.2},
          {"tmax", 9.8},
          {"prcp", 48},
          {"wspd", 14.7},
          {"pres", 1019.6},
          {"tsun", 3000}
      }
  };

  w->FetchData("London");
  nlohmann::json result = w->GetJson();

  ASSERT_TRUE(result.contains("data")) << "The JSON response does not contain 'data' field.";
  ASSERT_EQ(correct.at("data").at(0), result.at("data").at(0)) << "The fetched data does not match the expected data.";
}