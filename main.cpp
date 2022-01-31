#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <cstdio>
#include <stdio.h>

int main(int, char**) {
  boost::beast::http::response<boost::beast::http::string_body> response{boost::beast::http::status::ok, 11};
  boost::beast::http::response_serializer<boost::beast::http::string_body> serializer{response};
  boost::asio::io_context io_context{};
  std::FILE* file{std::fopen("/tmp/beastissue2221.out", "w")};
  boost::asio::posix::stream_descriptor stream{io_context.get_executor(), ::fileno(file)};
  boost::beast::http::async_write_header(
      stream, serializer,
      [](boost::system::error_code, std::size_t) {
      });
  io_context.run();
  boost::beast::http::response_serializer<boost::beast::http::string_body> serializer2{std::move(serializer)};
  std::fclose(file);
}
