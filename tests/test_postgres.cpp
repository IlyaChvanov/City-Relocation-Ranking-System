#include "postgres_db_manager.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"
#include <memory>

struct PostgresTest : public testing::Test {
  std::string dbname = "CityRelocation";
  std::string user = "postgres";
  std::string password = "58915891i";

  std::string connection_str =
      "dbname=" + dbname +
      " user=" + user +
      " password=" + password;

  std::unique_ptr<PostgresDBManager> DB;
  std::unique_ptr<pqxx::connection> conn;
  std::unique_ptr<City> test_city;

  void SetUp() override {
    conn = std::make_unique<pqxx::connection>(connection_str);
    DB = std::make_unique<PostgresDBManager>();
    test_city = std::make_unique<City>("london", 1.0, 2.0, 3.0, 4.0, 5);
    DB->InsertCity(*test_city);
  }

  void TearDown() override {
    DB->DeleteCity("london");
    DB->DeleteCity("first");
    DB->DeleteCity("second");
    DB->DeleteCity("third");
  }
};

TEST_F(PostgresTest, InsertCity) {
  pqxx::read_transaction read_txn(*conn);
  pqxx::result res = read_txn.exec("SELECT * FROM Cities WHERE city_name = 'london'");
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res[0]["city_name"].as<std::string>(), test_city->name);
  EXPECT_DOUBLE_EQ(res[0]["climate_points"].as<double>(), test_city->points_climate);
  EXPECT_DOUBLE_EQ(res[0]["life_quality_points"].as<double>(), test_city->points_life_quality);
  EXPECT_DOUBLE_EQ(res[0]["language_points"].as<double>(), test_city->points_language);
  EXPECT_DOUBLE_EQ(res[0]["common_points"].as<double>(), test_city->points_common);
  EXPECT_EQ(res[0]["rating_position"].as<int>(), test_city->rating_position);
}

TEST_F(PostgresTest, GetCity) {
  const auto london = DB->GetCity("london");
  EXPECT_EQ(london.name, test_city->name);
  EXPECT_EQ(london.points_climate, test_city->points_climate);
  EXPECT_EQ(london.points_language, test_city->points_language);
  EXPECT_EQ(london.points_common, test_city->points_common);
  EXPECT_EQ(london.points_life_quality, test_city->points_life_quality);
  EXPECT_EQ(london.rating_position, test_city->rating_position);
}


bool operator==(const City& first, const City& second) {
  return first.name == second.name;
}
TEST_F(PostgresTest, GetCities) {
  City first{"first", 1.0, 1.0, 1.0, 1.0, 1};
  City second{"second", 1.0, 1.0, 1.0, 1.0, 2};
  City third{"third", 1.0, 1.0, 1.0, 1.0, 3};
  DB->InsertCity(first);
  DB->InsertCity(second);
  DB->InsertCity(third);

  const auto cities = DB->GetCities(3);
  std::vector<City> correct{first, second, third};
  EXPECT_EQ(cities.size(), 3);
  EXPECT_EQ(cities, correct);
}

TEST_F(PostgresTest, GetCountryLifeQuality) {
  EXPECT_DOUBLE_EQ(DB->GetCountryLifeQuality("Denmark"), 84.55);
  EXPECT_THROW(DB->GetCountryLifeQuality("Neverland"), NoDataInDB);
}

TEST_F(PostgresTest, GetRankOfLanguage) {
  EXPECT_EQ(DB->GetRankOfLanguage("English"), 1);
  EXPECT_EQ(DB->GetRankOfLanguage("a_non_existing_lang"), -1);
}