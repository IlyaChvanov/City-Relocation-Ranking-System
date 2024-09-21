#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_I_DATA_ANALYSIS_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_I_DATA_ANALYSIS_H_

#include "nlohmann/json.hpp"

#include "city.h"

class IDataAnalysis {
 public:
  virtual ~IDataAnalysis() = default;
  virtual void Analyse() = 0;
  virtual double GetPoints() const = 0;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM_INCLUDE_I_DATA_ANALYSIS_H_
