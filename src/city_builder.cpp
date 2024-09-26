#include "city_builder.h"
#include "weather_data_collector.h"
#include "weather_analysis.h"
#include "language_data_collector.h"
#include "language_analysis.h"
#include "life_quality_data_collector.h"
#include "postgres_db_manager.h"
#include "UI.h"

std::unique_ptr<const City> CityBuilder::Build(const std::string& city_name,
                                               const std::string& country_name) {
  auto db_manager = std::make_unique<PostgresDBManager>();
  city_.name = city_name;
  city_.country = country_name;
  city_.language = db_manager->GetLanguageFromCountry(country_name);
  city_.points_language = CollectLanguagePoints();
  city_.points_climate = CollectWeatherPoints();
  city_.points_life_quality = CollectLifeQualityPoints();
  city_.points_common = CountCommonPoints();
  return std::make_unique<const City>(city_);
}

double CityBuilder::CollectWeatherPoints() const {
  auto weather_collector = std::make_unique<WeatherDataCollector>();
  weather_collector->FetchData(city_.name);
  WeatherAnalysis weather_analysis(weather_collector->GetJson());
  weather_analysis.Analyse();
  return weather_analysis.GetPoints();
}

double CityBuilder::CollectLifeQualityPoints() const {
  auto life_quality_data_collector = std::make_unique<LifeQualityDataCollector>();
  life_quality_data_collector->FetchData(city_.country);
  return life_quality_data_collector->GetLifeQualityPoints();
}

double CityBuilder::CollectLanguagePoints() const {
  auto db_manager = std::make_unique<PostgresDBManager>();
  auto language_data_collector = std::make_unique<LanguageDataCollector>();
  language_data_collector->FetchData(city_.language);
  LanguageAnalysis language_analysis(db_manager->GetRankOfLanguage(city_.language));
  language_analysis.Analyse();
  return language_analysis.GetPoints();
}

//let every scale weight equally
double CityBuilder::CountCommonPoints() const {
  return (city_.points_life_quality  + city_.points_language +
         city_.points_climate) / 3;
}