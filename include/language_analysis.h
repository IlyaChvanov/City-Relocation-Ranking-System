#ifndef CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_ANALYSIS_H_
#define CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_ANALYSIS_H_

#include "i_data_analysis.h"

class LanguageAnalysis : public IDataAnalysis {
 public:
  explicit LanguageAnalysis(int lang_pos);
  void Analyse() override;
  double GetPoints() const override;
 private:
  int language_position_;
  double points_;
};

#endif //CITY_RELOCATION_RANKING_SYSTEM_INCLUDE_LANGUAGE_ANALYSIS_H_
