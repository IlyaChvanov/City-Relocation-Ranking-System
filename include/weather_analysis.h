#ifndef CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_
#define CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_

#include "i_data_analysis.h"

class WeatherAnalysis : public IDataAnalysis{
 public:
  void Analise(const nlohmann::json& data) override;
 private:
  void ParseJson(const nlohmann::json& data) override;
  std::vector<double> temperatures_;
  double avg_temp_;
  double points_;
};


#endif //CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_
