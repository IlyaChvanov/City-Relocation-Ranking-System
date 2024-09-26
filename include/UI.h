#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_

#include <vector>
#include <memory>
#include <string_view>

#include "city.h"
#include "i_db_manager.h"

using DB = std::shared_ptr<const IDBManager>;
class UI {
 public:
  explicit UI(DB db);
  void Begin();
  void PrintTopCities(size_t cities_num) const;
  std::string AskAndGetCity() const;
  std::string AskAndGetCountry() const;
  void PrintCity(const City& city) const;
 private:
  const DB db_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
