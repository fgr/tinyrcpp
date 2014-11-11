#ifndef DEMO1_IFACE_H_
#define DEMO1_IFACE_H_

class point2d {
public:
  point2d(double x, double y) : x_{ x }, y_{ y } {}

  double const &x() const { return x_; }
  double const &y() const { return y_; }

private:
  const double x_, y_;
};

class vector2d {
public:
  vector2d(point2d const &p1, point2d const &p2) : p1_{ p1 }, p2_{ p2 } {}

  point2d const &p1() const { return p1_; }
  point2d const &p2() const { return p2_; }

private:
  point2d p1_, p2_;
};

class demo1_iface {
public:
  virtual ~demo1_iface() = default;
  virtual double length(vector2d const &) = 0;
};

#endif // DEMO1_IFACE_H_

