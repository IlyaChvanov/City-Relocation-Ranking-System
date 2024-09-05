#include "i_data_collector.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;
using json = nlohmann::json;
nlohmann::json IDataCollector::PerformGetRequest(const std::string& host,
                                                 const std::string& target,
                                                 const std::string& api_key) const {
  asio::io_context ioc;
  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);
  const auto ips = resolver.resolve(host, "80");
  stream.connect(ips);

  http::request<http::string_body> req{http::verb::get, target, 11};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, "Boost.Beast");

  if (!api_key.empty()) {
    req.set(http::field::authorization, "Bearer " + api_key);
  }

  http::write(stream, req);
  beast::flat_buffer buffer;
  http::response<http::dynamic_body> result;
  http::read(stream, buffer, result);

  if (result.result() != http::status::ok) {
    std::cerr << "HTTP Error: " << result.result_int() << std::endl;
    return {};
  }

  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);
  if (ec && ec != beast::errc::not_connected) {
    throw beast::system_error{ec};
  }
  return json::parse(beast::buffers_to_string(result.body().data()));
}