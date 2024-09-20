#include "life_quality_data_collector.h"
#include "postgres_db_manager.h"

#include "pqxx/pqxx"

void LifeQualityDataCollector::FetchData(const std::string& country) {
  PostgresDBManager DB;
  points_ = DB.GetCountryLifeQuality(country);
}

double LifeQualityDataCollector::GetLifeQualityPoints() const {
  return points_;
}
