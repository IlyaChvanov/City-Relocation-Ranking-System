#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_DATA_COLLECTOR_H_

#include "i_data_collector.h"

class LifeQualityDataCollector : public IDataCollector {
 public:
  void FetchData(const std::string& city);
  double GetLifeQualityPoints() const;
 private:
  double points_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_DATA_COLLECTOR_H_
