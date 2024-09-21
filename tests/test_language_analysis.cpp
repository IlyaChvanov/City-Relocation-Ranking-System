#include "gtest/gtest.h"
#include "language_analysis.h"

TEST(LanguageAnalysis, Analyse) {
  LanguageAnalysis analyser_eng_lang(1);
  LanguageAnalysis analyser_thai_lang(51);
  analyser_eng_lang.Analyse();
  analyser_thai_lang.Analyse();
  ASSERT_EQ(analyser_eng_lang.GetPoints(), 10.0);
  ASSERT_EQ(analyser_thai_lang.GetPoints(), 2.0);
}