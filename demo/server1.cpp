#include <iostream>

#include "communication.hpp"

using std::vector;
using asio::ip::tcp;
using namespace tinyrcpp;

int main()
{
  try
  {
    // Any program that uses asio need to have at least one io_service object
    asio::io_service io_service;

    // acceptor object needs to be created to listen for new connections
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1313));

    for (;;)
    {
      // creates a socket
      tcp::socket socket(io_service);

      // wait and listen
      acceptor.accept(socket);

      // prepare message to send back to client
      bool b = true;
      write_bool(socket, b);

      // vector<asio::const_buffer> buffers;
      // buffers.push_back( asio::buffer(&b, sizeof(b) ) );
      //buffers.push_back( asio::buffer(&i, sizeof(i) ) );
      //buffers.push_back( asio::buffer(&c, sizeof(c) ) );
      // std::size_t length = asio::write( socket, buffers );

      try {
	      throw std::runtime_error("Test exception");
      } catch(std::runtime_error const& ex) {
	      write_string(socket, ex.what());
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

