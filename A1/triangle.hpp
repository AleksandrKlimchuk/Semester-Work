#ifndef KLIMCHUK_TRIANGLE
#define KLIMCHUK_TRIANGLE

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& firstTop, const point_t& secondTop, const point_t& thirdTop);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& point) override;
  void move(double moveAbscissa, double moveOrdinate) override;
  point_t getCentre() const;
private:
  point_t a_;
  point_t b_;
  point_t c_;
};

#endif
