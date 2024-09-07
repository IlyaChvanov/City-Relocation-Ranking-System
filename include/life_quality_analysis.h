#ifndef CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_ANALYSIS_H_
#define CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_ANALYSIS_H_

#include "i_data_analysis.h"

class LifeQualityAnalysys : public IDataAnalysis {
 public:
  void Analise(const nlohmann::json& data) override;
 private:
  void ParseJson(const nlohmann::json& data) override;
  double points_;
};

#endif //CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LIFE_QUALITY_ANALYSIS_H_
