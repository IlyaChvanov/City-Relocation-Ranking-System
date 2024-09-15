#include "postgres_db_manager.h"

#include "iostream"
PostgresDBManager::PostgresDBManager() {
  std::string dbname = "CityRelocation";
  std::string user = "postgres";
  std::string password = "58915891i";

  std::string connection_str = "dbname=" + dbname +
      " user=" + user +
      " password=" + password;

  connection_ = std::make_shared<pqxx::connection>(connection_str);
  if (!connection_->is_open()) {
    throw DBConnectionError("Failed to connect Postgres");
  }
}

void PostgresDBManager::InsertCity(const City& city)  {
  try {
    std::string city_name;
    std::transform(city.name.begin(), city.name.end(), std::back_inserter(city_name),
                   [](const char c) { return tolower(c); });
    pqxx::work txn(*connection_);
    std::string query = "INSERT INTO Cities (city_name, climate_points, life_quality_points, language_points, common_points, rating_position) "
                        "VALUES (" +
        txn.quote(city_name) + ", " +
        txn.quote(city.points_climate) + ", " +
        txn.quote(city.points_life_quality) + ", " +
        txn.quote(city.points_language) + ", " +
        txn.quote(city.points_common) + ", " +
        txn.quote(city.rating_position) + ")";

    txn.exec(query);
    txn.commit();
    std::cout << "City inserted successfully" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error inserting city: " << e.what() << std::endl;
  }
}

std::vector<City> PostgresDBManager::GetCities(size_t num) const {
  std::vector<City> ans;
  ans.reserve(num);
  pqxx::read_transaction txn(*connection_);
  std::string query = "SELECT * FROM Cities "
                      "ORDER BY rating_position "
                      "LIMIT " + std::to_string(num);
  const auto result = txn.exec(query);
  auto row_to_city = [](const pqxx::row& row) {
    return City{
        row.at("city_name").as<std::string>(),
        row.at("climate_points").as<double>(),
        row.at("language_points").as<double>(),
        row.at("life_quality_points").as<double>(),
        row.at("common_points").as<double>(),
        row.at("rating_position").as<int>()
    };
  };
  std::transform(result.begin(), result.end(), std::back_inserter(ans), row_to_city);
  return ans;
}

City PostgresDBManager::GetCity(const std::string& city) const {
  std::string city_name;
  std::transform(city.begin(), city.end(), std::back_inserter(city_name),
                 [](const char c) { return tolower(c); });

  pqxx::read_transaction txn(*connection_);
  std::string query = "SELECT * FROM Cities "
                      " WHERE city_name = " +  MakeCorrectName(city);
  const auto result = txn.exec(query);
  if (result.empty()) {
    std::cerr << "City not found" << '\n';
    throw NoCityInDB("city not found");
  }
  City response;
  const pqxx::row row = result[0];
  response.name = row["city_name"].as<std::string>();
  response.points_climate = row["climate_points"].as<double>();
  response.points_life_quality = row["life_quality_points"].as<double>();
  response.points_language = row["language_points"].as<double>();
  response.points_common = row["common_points"].as<double>();
  response.rating_position= row["rating_position"].as<int>();

  return response;
}
void PostgresDBManager::DeleteCity(const std::string& city) const {
  pqxx::work txn(*connection_);
  const std::string query = "DELETE FROM Cities "
                            "WHERE city_name = " + MakeCorrectName(city);
  txn.exec(query);
  txn.commit();
}
std::string PostgresDBManager::MakeCorrectName(const std::string& name) const {
  std::string city_name;
  std::transform(name.begin(), name.end(), std::back_inserter(city_name),
                 [](const char c) { return tolower(c); });
  return connection_->quote(city_name);
};