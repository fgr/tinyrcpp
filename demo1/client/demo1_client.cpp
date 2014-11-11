#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"

#include <iostream>

#include "demo1_iface.hpp"
#include "demo1_rcp_common.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;

class demo1_client_facade : public demo1_iface {
public:
  virtual double length(vector2d const &v) override {
    tcp::iostream s("localhost", "1313");
    boost::archive::binary_oarchive oarchive{ s };

    {
      const auto &service_id = service_ids::length;
      oarchive << service_id;
      s.flush();
    }
    {
      const auto &x = v.p1().x();
      const auto &y = v.p1().y();
      oarchive << x << y;
      s.flush();
    }
    {
      const auto &x = v.p2().x();
      const auto &y = v.p2().y();
      oarchive << x << y;
      s.flush();
    }

    boost::archive::binary_iarchive iarchive{ s };
    double result;
    iarchive >> result;
    return result;
  }
};

int main() {
  demo1_client_facade service;
  vector2d v{ point2d{ 1, 1 }, point2d{ 3, 3 } };
  return service.length(v);
}

