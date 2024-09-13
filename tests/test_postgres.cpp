#include "postgres_db_manager.h"
#include "gtest/gtest.h"
#include "pqxx/pqxx"

struct PostgresTest : public testing::Test {
  std::string dbname = "CityRelocation";
  std::string user = "postgres";
  std::string password = "58915891i";

  std::string connection_str =
      "dbname=" + dbname +
      " user=" + user +
      " password=" + password;

  PostgresDBManager* DB;
  pqxx::connection* conn = new pqxx::connection(connection_str);
  City* test_city;
  pqxx::work* txn;
  void SetUp() override {;
    DB = new PostgresDBManager;
    test_city = new City{"london", 1.0, 2.0, 3.0, 4.0, 1};
    txn = new pqxx::work(*conn);
    DB->InsertCity(*test_city);
  }
  void TearDown() override {
    txn->exec("DELETE FROM Cities WHERE city_name = 'london'");
    txn->commit();
    delete DB;
    delete test_city;
    delete conn;
  }
};

TEST_F(PostgresTest, InsertCity) {
  pqxx::result res = txn->exec("SELECT * FROM Cities WHERE city_name = 'london'");
  EXPECT_EQ(res.size(), 1);
  EXPECT_EQ(res[0]["city_name"].as<std::string>(), test_city->name);
  EXPECT_DOUBLE_EQ(res[0]["climate_points"].as<double>(), test_city->points_climate);
  EXPECT_DOUBLE_EQ(res[0]["life_quality_points"].as<double>(), test_city->points_life_quality);
  EXPECT_DOUBLE_EQ(res[0]["language_points"].as<double>(), test_city->points_language);
  EXPECT_DOUBLE_EQ(res[0]["common_points"].as<double>(), test_city->points_common);
  EXPECT_EQ(res[0]["rating_position"].as<int>(), test_city->rating_position);

  txn.exec("DELETE FROM Cities WHERE city_name = 'London'");
  txn.commit();
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