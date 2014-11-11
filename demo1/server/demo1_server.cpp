#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

#include <iostream>

#include "demo1_iface.hpp"
#include "demo1_rcp_common.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;

class demo1_impl : public demo1_iface {
public:
  virtual ~demo1_impl() override = default;
  virtual double length(vector2d const &v) override { return 42; }
};

class server {
public:
  server(demo1_impl *service) : service_{ service } {}

  void activate() {
    io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1313));
    std::cout << "S: accepting..." << std::endl;
    tcp::iostream s;
    acceptor.accept(*s.rdbuf());
    std::cout << "S: accepted..." << std::endl;
    boost::archive::binary_iarchive iarchive{ s };
    std::cout << "S: 1" << std::endl;

    service_ids service_id;
    iarchive >> service_id;
    std::cout << "S: service_id=" << as_integer(service_id) << std::endl;

    switch(service_id) {
    case service_ids::length:
      double x, y;
      iarchive >> x >> y;
      point2d p1{ x, y };
      iarchive >> x >> y;
      point2d p2{ x, y };
      vector2d v{ p1, p2 };
      auto result = service_->length(v);
      boost::archive::binary_oarchive oarchive{ s };
      oarchive << result;
      s.close();
      break;
    }

  }

private:
  demo1_iface *service_;
};

int main() {
  demo1_impl demo1;
  server s{ &demo1 };
  s.activate();
}

