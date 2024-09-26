#include "pqxx/pqxx"
#include "nlohmann/json.hpp"
#include "weather_data_collector.h"
#include "weather_analysis.h"
#include "postgres_db_manager.h"
#include "UI.h"
#include "city_builder.h"
#include "iostream"

int main() {
  auto db_manager = std::make_shared<PostgresDBManager>();
  UI ui(db_manager);

  std::string city_name = ui.AskAndGetCity();
  const auto city = db_manager->GetCity(city_name);
  if (city) {
    ui.PrintCity(city.value());
  } else {
    try {
      CityBuilder builder;
      auto city = builder.Build(city_name, ui.AskAndGetCountry());
      db_manager->InsertCity(*city);
      ui.PrintCity(*city);
    } catch (...) {
      return 0;
    }
  }
  return 0;
}