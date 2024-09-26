#include "UI.h"

#include <iostream>
#include <iterator>
#include <utility>
#include "i_db_manager.h"

UI::UI(DB  db) : db_(std::move(db)) {}

using std::cout;
void UI::PrintTopCities(size_t cities_num) const {
  for (const auto& city : db_->GetCities(cities_num)) {
    cout << city.rating_position << ": " << "\033[1m" << city.name << "\033[1m" << '\n'
    << "climate: " << city.points_climate << '\n'
    << "life quality: " << city.points_life_quality << '\n'
    << "language complexity: " << city.points_language << '\n'
    << "points in common: " << city.points_common << '\n'
    << "_______________________________" << '\n';
  }
}

using std::string;
string UI::AskAndGetCity() const {
  cout << "Enter the city you want to evaluate: " << '\n';
  string city;
  std::cin >> city;
  return city;
}

string UI::AskAndGetCountry() const {
  cout << "Enter the country name: " << '\n';
  string country;
  std::cin >> country;
  return country;
}

void UI::PrintCity(const City& city) const {
  cout << city.rating_position << ": " << "\033[1m" << city.name << "\033[1m" << '\n'
       << "climate: " << city.points_climate << '\n'
       << "life quality: " << city.points_life_quality << '\n'
       << "language complexity: " << city.points_language << '\n'
      << "points in common: " << city.points_common;
}
