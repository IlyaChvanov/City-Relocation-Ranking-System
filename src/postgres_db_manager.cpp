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
    pqxx::work txn(*connection_);
    std::string query = "INSERT INTO Cities (city_name, climate_points, life_quality_points, language_points, common_points, rating_position) "
                        "VALUES (" +
        txn.quote(city.name) + ", " +
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
std::vector<City> PostgresDBManager::GetCities(size_t num) const {};
City PostgresDBManager::GetCity(std::string_view city) const {};