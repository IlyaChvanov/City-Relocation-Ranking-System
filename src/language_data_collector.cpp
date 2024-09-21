#include "language_data_collector.h"
#include "postgres_db_manager.h"

void LanguageDataCollector::FetchData(const std::string& language) {
  PostgresDBManager DB;
  rank_ = DB.GetRankOfLanguage(language);
}

int LanguageDataCollector::GetLanguageRank() const {
  return rank_;
}
