#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_

#include "city.h"

#include <vector>

class IDBManager {
 public:
  virtual std::vector<City> GetCities(size_t num) const = 0;
  virtual City GetCity(std::string_view city) const = 0;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__I_DB_MANAGER_H_
