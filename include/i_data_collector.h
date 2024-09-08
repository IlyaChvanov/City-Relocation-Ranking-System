#ifndef COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_
#define COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_

#include <string_view>
#include "exception"

#include "nlohmann/json.hpp"


class IDataCollector {
 public:
  virtual void FetchData(const std::string& city) = 0;
  virtual ~IDataCollector() = default;
 protected:
  nlohmann::json PerformGetRequest(const std::string& host,
                                   const std::string& target,
                                   const std::string& api_key = "") const;
};

class ErrorConnect : public std::exception {
 public:
  ErrorConnect(const std::string& error) : message(error){};
  const char* what() const noexcept override {
    return message.c_str();
  }
 private:
  std::string message;
};

#endif //COUNTRY_RELOCATION_RANKING_SYSTEM__I_DATA_COLLECTOR_H_
