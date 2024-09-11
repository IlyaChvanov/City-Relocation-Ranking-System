#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_

#include "city.h"

#include <vector>

class IDBManager {
 public:
  virtual void InsertCity(const City& city)  = 0;
  virtual std::vector<City> GetCities(size_t num) const = 0;
  virtual City GetCity(std::string_view city) const = 0;
};

 class DBConnectionError : public std::exception {
 public:
  DBConnectionError(const std::string& error) : message(error) {}
  const char* what() noexcept { return message.c_str(); }
 private:
  const std::string message;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
