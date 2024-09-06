#include "i_data_collector.h"

#include "curl/curl.h"
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
  s->append(static_cast<char*>(contents), size * nmemb);
  return size * nmemb;
}

nlohmann::json IDataCollector::PerformGetRequest(const std::string& host,
                                                 const std::string& url,
                                                 const std::string& api_key) const {
  CURL* hnd = curl_easy_init();
  std::string response_string;

  if(hnd) {
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("x-rapidapi-key: " + api_key).c_str());
    headers = curl_slist_append(headers, ("x-rapidapi-host: " + host).c_str());
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Установка обратного вызова для записи данных в строку
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response_string);

    CURLcode ret = curl_easy_perform(hnd);

    if (ret != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << std::endl;
      return {};
    }

    // Освобождение ресурсов
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

    return nlohmann::json::parse(response_string);
  }

  return {};
}