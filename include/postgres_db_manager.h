#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_POSTGRES_DB_MANAGER_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_POSTGRES_DB_MANAGER_H_

#include "i_db_manager.h"

#include "pqxx/pqxx"

#include <memory>

class PostgresDBManager : public IDBManager{
 public:
  PostgresDBManager();
  void InsertCity(const City& city) override;
  std::vector<City> GetCities(size_t num) const override;
  City GetCity(const std::string& city) const override;
 private:
  std::shared_ptr<pqxx::connection> connection_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_POSTGRES_DB_MANAGER_H_
