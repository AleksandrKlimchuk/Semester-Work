#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(double width, double height, double posX, double posY):
  rectangle_{width, height, point_t{posX, posY}}
{
  assert((width > 0.0) && (height > 0.0));
}

double Rectangle::getArea() const
{
  return rectangle_.height * rectangle_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(const point_t& point)
{
  rectangle_.pos = point;
}

void Rectangle::move(double moveAbscissa, double moveOrdinate)
{
  rectangle_.pos.x += moveAbscissa;
  rectangle_.pos.y += moveOrdinate;
}

point_t Rectangle::getCentre() const
{
  return rectangle_.pos;
}
