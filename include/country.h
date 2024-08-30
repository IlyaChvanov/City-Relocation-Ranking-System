#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_COUNTRY_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_COUNTRY_H_

#include <string>

struct Country {
  std::string name;
  double points_climate;
  double points_life_quality;
  double points_language;
  int rating_position;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_COUNTRY_H_
