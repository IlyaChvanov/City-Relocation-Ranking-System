#include "UI.h"

#include <utility>
#include "i_db_manager.h"

using std::cout;
void UI::PrintTopCountries(size_t countries_num) const {
  for (const auto& country : db_->LoadCountries(countries_num)) {
    cout << country.rating_position << ": " << "\033[1m" << country.name << "\033[1m" << '\n'
    << "climate: " << country.points_climate << '\n'
    << "life quality: " << country.points_life_quality << '\n'
    << "language complexity: " << country.points_language << '\n'
    << "_______________________________" << '\n';
  }
}
UI::UI(DB  db) : db_(std::move(db)) {}
