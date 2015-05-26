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

    // 1. Send request to server:
    {
      // 1.1 Send type of requested service (length service):
      const int service_id{ service_ids::get_vector_length };
      oarchive << service_id;
    }
    {
      // 1.2 Send first argument (data) required by length service:
      const auto &x = v.p1().x;
      const auto &y = v.p1().y;
      oarchive << x << y;
    }
    {
      // 1.3 Send second argument (data) required by length service:
      const auto &x = v.p2().x;
      const auto &y = v.p2().y;
      oarchive << x << y;
    }
    s.flush();

    // 2. Read (length service) response from server:
    boost::archive::binary_iarchive iarchive{ s };
    double result;
    iarchive >> result;
    return result;
  }
};

int main() {
  demo1_client_facade service;
  vector2d v{ point2d{ 1, 1 }, point2d{ 3, 3 } };
  const auto len = service.length(v);
  return len;
}

