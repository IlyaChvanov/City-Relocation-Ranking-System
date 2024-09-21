#ifndef CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_
#define CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_

#include "i_data_analysis.h"

class WeatherAnalysis : public IDataAnalysis {
 public:
  explicit WeatherAnalysis(nlohmann::json json);
  void Analyse() override;
  double GetPoints() const;
  double GetAvgTemp() const;
 private:
  void ParseJson(const nlohmann::json& data) override;
  std::vector<double> temperatures_;
  double avg_temp_;
  double points_; //0-10
  const double best_temp = 22.5;
  nlohmann::json data_;
};

class EmptyJson : public std::exception {
 public:
  explicit EmptyJson(const std::string& error) : message(error) {}
   const char* what() const noexcept override { return message.c_str(); }
 private:
  const std::string message;
};

#endif //CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_WEATHER_ANALYSIS_H_
