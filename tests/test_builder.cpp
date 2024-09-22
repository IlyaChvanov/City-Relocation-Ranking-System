#include "gtest/gtest.h"
#include "city_builder.h"

TEST(CityBuild, Build) {
  CityBuilder builder;
  auto city = builder.Build("London", "United Kingdom");
  EXPECT_DOUBLE_EQ(city->points_language, 10.0);
  EXPECT_DOUBLE_EQ(city->points_climate, 0.0);
  EXPECT_DOUBLE_EQ(city->points_life_quality, 7.995);
  EXPECT_DOUBLE_EQ(city->points_common, 5.998333333333334);
}