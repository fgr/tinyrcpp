#ifndef TINYRCPP_COMMUNICATION__H_
#define TINYRCPP_COMMUNICATION__H_

#include <cstdint>
#include <asio.hpp>

namespace tinyrcpp {

void write_bool(asio::ip::tcp::socket &, bool);
void write_uint8(asio::ip::tcp::socket &, std::uint8_t);
void write_uint32(asio::ip::tcp::socket &, std::uint32_t);
void write_string(asio::ip::tcp::socket &, std::string const &);

bool read_bool(asio::ip::tcp::socket &);
std::int8_t read_uint8(asio::ip::tcp::socket &);
std::int32_t read_uint32(asio::ip::tcp::socket &);
std::string read_string(asio::ip::tcp::socket &);

} // namespace tinyrcpp

#endif // TINYRCPP_COMMUNICATION__H_
