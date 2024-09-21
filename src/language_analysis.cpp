#include "language_analysis.h"

LanguageAnalysis::LanguageAnalysis(int lang_pos) : language_position_(lang_pos) {}

void LanguageAnalysis::Analyse() {
  if (language_position_ == 1) {
    points_ = 10.0;
  } else if (language_position_ < 10) {
    points_ = 7.0;
  } else if (language_position_ < 20) {
    points_ = 6.0;
  } else if (language_position_ < 30) {
    points_ = 5.0;
  } else if (language_position_ < 40) {
    points_ = 4.0;
  } else if (language_position_ < 50) {
    points_ = 3.0;
  } else {
    points_ = 2.0;
  }
}

double LanguageAnalysis::GetPoints() const {
  return points_;
}