#include <iostream>
#include "communication.hpp"

using asio::ip::tcp;
using namespace std;
using namespace tinyrcpp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <host> <port>" << std::endl;
      return 1;
    }

    asio::io_service io_service;

	tcp::resolver resolver(io_service);
	tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    asio::connect(socket, endpoint_iterator);

    for (;;) {
      std::error_code error;

      bool exception = read_bool(socket);

      std::cout << "exception? = " << exception << std::endl;

      if (exception) {
        auto msg = read_string(socket);
	std::cout << msg << std::endl;
        throw runtime_error(msg);
        // std::string error_message;
        // std::cout<<read_uint32(socket);
        // bytes_transferred = socket.receive(asio::buffer(&error_message));
      }

      int i;
      char c;

	  std::array<asio::mutable_buffer, 2> bufs = {
	  	asio::buffer(&i, sizeof(i)),
	  	asio::buffer(&c, sizeof(c)) };
      auto bytes_transferred = asio::read(socket, bufs, error);

      // boost::array<char, 128> buf;
      // size_t len = socket.read_some(asio::buffer(buf), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw std::system_error(error); // Some other error.

      // std::cout.write(buf.data(), len);
      std::cout << "i = " << i << std::endl;
      std::cout << "c = " << c << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
