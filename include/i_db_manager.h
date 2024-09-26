#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_

#include "city.h"

#include <vector>
#include <optional>

class IDBManager {
 public:
  virtual void InsertCity(const City& city)  = 0;
  virtual std::vector<City> GetCities(size_t num) const = 0;
  virtual std::optional<City> GetCity(const std::string& city) const = 0;
  virtual void DeleteCity(const std::string& city) const = 0;
  virtual double GetCountryLifeQuality(const std::string& country) const = 0;
  virtual int GetRankOfLanguage(const std::string& language) const = 0;
  virtual std::string GetLanguageFromCountry(const std::string& country) const = 0;
};

class DBConnectionError : public std::exception {
 public:
  DBConnectionError(const std::string& error) : message(error) {}
  const char* what() const noexcept override { return message.c_str(); }
 private:
  const std::string message;
};

class NoDataInDB : public std::exception {
  public:
  explicit NoDataInDB(const std::string& error) : message(error) {}
  const char* what() const noexcept { return  message.c_str(); }
 private:
  const std::string message;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
