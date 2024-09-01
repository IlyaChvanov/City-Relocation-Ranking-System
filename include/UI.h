#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_

#include <vector>
#include <memory>
#include <string_view>

#include "city.h"
#include "i_db_manager.h"

//TODO Дописать тест на Print, когда появится БД
using DB = std::shared_ptr<const IDBManager>;
class UI {
 public:
  explicit UI(DB db);
  void PrintTopCities(size_t cities_num) const;
  std::string AskAndGetCity() const;
  void PrintCity(std::string_view city) const;
 private:
  const DB db_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
