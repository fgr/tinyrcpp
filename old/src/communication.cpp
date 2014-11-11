#include "communication.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <asio.hpp>

namespace tinyrcpp {

using std::uint8_t;
using std::string;
using std::uint32_t;
using std::error_code;
using std::runtime_error;
using std::unique_ptr;
using asio::ip::tcp;

void write_bool(tcp::socket &s, bool b) {
  if (b)
    write_uint8(s, 1);
  else
    write_uint8(s, 0);
}

void write_uint8(tcp::socket &s, uint8_t i) {
  auto bytes_to_write = sizeof(i);
  error_code error;
  auto bytes_written = asio::write(s, asio::buffer(&i, bytes_to_write), error);
  if (bytes_written != bytes_to_write ||
      (error && (error != asio::error::eof))) {
    throw runtime_error("Could not write std::uint_t");
  }
}

void write_uint32(tcp::socket &s, uint32_t i) {
  i = htonl(i);
  auto bytes_to_write = sizeof(i);
  error_code error;
  auto bytes_written = asio::write(s, asio::buffer(&i, bytes_to_write), error);
  if (bytes_written != bytes_to_write ||
      (error && (error != asio::error::eof))) {
    throw runtime_error("Could not write std::uint32_t");
  }
}

void write_string(tcp::socket &s, string const &str) {
  auto bytes_to_write = str.length();
  write_uint32(s, bytes_to_write);

  error_code error;
  auto bytes_written = asio::write(s, asio::buffer(str, bytes_to_write), error);
  if (bytes_written != bytes_to_write ||
      (error && (error != asio::error::eof))) {
    throw runtime_error("Could not write std::string");
  }
}

bool read_bool(tcp::socket &s) {
   uint8_t i = read_uint8(s);
   if(i)
     return true;
   else
     return false;
}

int8_t read_uint8(tcp::socket &s) {
  uint8_t i;
  error_code error;
  auto bytes_to_read = sizeof(i);
  auto bytes_read = asio::read(s, asio::buffer(&i, bytes_to_read), error);
  if(bytes_read != bytes_to_read || (error && (error != asio::error::eof))) {
		throw runtime_error("Could not read std::uint8_t");
  }
  return i;
}

int32_t read_uint32(tcp::socket &s) {
  uint32_t i;
  error_code error;
  auto bytes_to_read = sizeof(i);
  auto bytes_read = asio::read(s, asio::buffer(&i, bytes_to_read), error);
  if(bytes_read != bytes_to_read || (error && (error != asio::error::eof))) {
		throw runtime_error("Could not read std::uint32_t");
  }
  i = ntohl(i);
  return i;
}

string read_string(tcp::socket &s) {
  auto bytes_to_read = read_uint32(s);
  unique_ptr<char> buf{ new char[bytes_to_read] };
  error_code error;
  auto bytes_read =
      asio::read(s, asio::buffer(buf.get(), bytes_to_read), error);
  return string{ buf.get(), bytes_read };
}

} // namespace tinyrcpp

