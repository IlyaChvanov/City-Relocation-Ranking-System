#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_CITY_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_CITY_H_

#include <string>

struct City {
  std::string name;
  double points_climate;
  double points_life_quality;
  double points_language;
  double points_common; //0-10
  int rating_position;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_CITY_H_
