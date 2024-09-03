#include "gtest/gtest.h"

#include "weather_data_collector.h"

TEST(CoordFromName, London) {
  WeatherDataCollector w;
  CityCoord london = {51.5073, -0.127647};
  CityCoord result = w.CoordFromName("London");

  const double epsilon = 1e-1; // epsilon = 1e-1: это примерно 11
  // км (этого обычно достаточно для идентификации одного города)

  ASSERT_NEAR(london.lat, result.lat, epsilon);
  ASSERT_NEAR(london.lon, result.lon, epsilon);
}