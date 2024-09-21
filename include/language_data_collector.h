#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_DATA_COLLECTOR_H_

#include "i_data_collector.h"

class LanguageDataCollector : public IDataCollector {
 public:
  void FetchData(const std::string& language) override;
  int GetLanguageRank() const;
 private:
  int rank_;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_DATA_COLLECTOR_H_
