#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_

#include <vector>
#include <memory>
#include <iostream>

#include "country.h"
#include "i_db_manager.h"

//TODO Дописать тест на Print, когда появится БД
using DB = std::shared_ptr<const IDBManager>;
class UI {
 public:
  explicit UI(DB  db);
  void PrintTopCountries(size_t countries_num) const;//takes from DB
 private:
  const DB db_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__UI_H_
