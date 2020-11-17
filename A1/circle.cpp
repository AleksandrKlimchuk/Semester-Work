#include "circle.hpp"

#include <cmath>
#include <cassert>

Circle::Circle(double posX, double posY, double radius):
  radius_ {radius},
  centre_ {posX, posY}
{
  assert(radius > 0.0);
}

double Circle::getArea() const
{
  return  M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t {2 * radius_, 2 * radius_, centre_};
}

void Circle::move(const point_t& point)
{
  centre_ = point;
}

void Circle::move(double moveAbscissa, double moveOrdinate)
{
  centre_.x += moveAbscissa;
  centre_.y += moveOrdinate;
}

point_t Circle::getCentre() const
{
  return centre_;
}
