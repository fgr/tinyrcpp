#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

#include <iostream>
#include <stdexcept>

#include "demo1_iface.hpp"
#include "demo1_rcp_common.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;

//////////////////////////////////////////////////////////////////////

class demo1_impl : public demo1_iface {
public:
  virtual ~demo1_impl() override = default;
  virtual double length(vector2d const &v) override;
};

//////////////////////////////////////////////////////////////////////

class server {
public:
  server(demo1_impl &service)
      : service_ /*{*/(service) /*}*/ /* http://stackoverflow.com/questions/10509603/why-cant-i-initialize-a-reference-in-an-initializer-list-with-uniform-initializ */ {
  }

  void activate() {
    io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1313));
    std::cout << "Server: Waiting for connections..." << std::endl;
    tcp::iostream s;
    acceptor.accept(*s.rdbuf());
    std::cout << "Server: Connection established." << std::endl;
    boost::archive::binary_iarchive iarchive{ s };

    int service_id;
    iarchive >> service_id;
    std::cout << "Server: service_id=" << service_id << std::endl;

    boost::archive::binary_oarchive oarchive{ s };
    switch(service_id) {
    case service_ids::get_vector_length:
      length_request_indicated(iarchive, oarchive);
      s.close();
      break;
    default:
      throw std::runtime_error("Unknown service requested: " + service_id);
    }
  }

private:
  demo1_iface &service_;
  void length_request_indicated(boost::archive::binary_iarchive &in,
                                boost::archive::binary_oarchive &out);
};

//////////////////////////////////////////////////////////////////////

int main() {
  demo1_impl demo1;
  server s{ demo1 };
  s.activate();
}

//////////////////////////////////////////////////////////////////////

double demo1_impl::length(vector2d const &v) {
  auto lenx = std::abs(v.p1().x - v.p2().x);
  auto leny = std::abs(v.p1().y - v.p2().y);
  return std::sqrt((lenx * lenx) + (leny * leny));
}

//////////////////////////////////////////////////////////////////////

void server::length_request_indicated(boost::archive::binary_iarchive &in,
                                      boost::archive::binary_oarchive &out) {
  double x, y;
  in >> x >> y;
  point2d p1{ x, y };
  in >> x >> y;
  point2d p2{ x, y };
  vector2d v{ p1, p2 };
  auto result = service_.length(v);
  out << result;
}

//////////////////////////////////////////////////////////////////////

