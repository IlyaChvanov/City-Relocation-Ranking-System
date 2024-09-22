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
  PostgresDBManager postgres_db_manager;
  city_.name = city_name;
  city_.country = country_name;
  city_.language = postgres_db_manager.GetLanguageFromCountry(country_name);
  city_.points_language = CollectLanguagePoints();
  city_.points_climate = CollectWeatherPoints();
  city_.points_life_quality = CollectLifeQualityPoints();
  city_.points_common = CountCommonPoints();
  return std::make_unique<const City>(city_);
}

double CityBuilder::CollectWeatherPoints() const {
  WeatherDataCollector weather_collector;
  weather_collector.FetchData(city_.name);
  WeatherAnalysis weather_analysis(weather_collector.GetJson());
  weather_analysis.Analyse();
  return weather_analysis.GetPoints();
}

double CityBuilder::CollectLifeQualityPoints() const {
  LifeQualityDataCollector life_quality_data_collector;
  life_quality_data_collector.FetchData(city_.country);
  return life_quality_data_collector.GetLifeQualityPoints();
}

double CityBuilder::CollectLanguagePoints() const {
  PostgresDBManager db_manager;
  LanguageDataCollector language_data_collector;
  language_data_collector.FetchData(city_.language);
  LanguageAnalysis language_analysis(db_manager.GetRankOfLanguage(city_.language));
  language_analysis.Analyse();
  return language_analysis.GetPoints();
}

//let every scale weight equally
double CityBuilder::CountCommonPoints() const {
  return (city_.points_life_quality  + city_.points_language +
         city_.points_climate) / 3;
}