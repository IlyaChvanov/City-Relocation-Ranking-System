#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_

#include <string_view>

#include "nlohmann/json.hpp"


class IDataCollector {
 public:
  virtual void FetchData(const std::string& city) = 0;
  virtual std::pair<std::string, std::string> GetParsedData() = 0;
  virtual ~IDataCollector() = default;
 protected:
  virtual void ParseData(const nlohmann::json& json) = 0;
  nlohmann::json PerformGetRequest(const std::string& host,
                                   const std::string& target) const;
};



#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_
