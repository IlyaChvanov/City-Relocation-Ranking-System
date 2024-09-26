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
  std::optional<City> GetCity(const std::string& city) const override;
  void DeleteCity(const std::string& city) const override;
  double GetCountryLifeQuality(const std::string& country) const override;
  int GetRankOfLanguage(const std::string& language) const override;
  std::string GetLanguageFromCountry(const std::string& country) const override;
 private:
  std::string MakeCorrectName(const std::string& name) const;
  std::shared_ptr<pqxx::connection> connection_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_POSTGRES_DB_MANAGER_H_
