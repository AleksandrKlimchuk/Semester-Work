#include "triangle.hpp"
#include <algorithm>
#include <cassert>

Triangle::Triangle(const point_t& firstTop, const point_t& secondTop, const point_t& thirdTop):
  a_(firstTop),
  b_(secondTop),
  c_(thirdTop)
{
  assert(((a_.x != b_.x) || (a_.y != b_.y)) && ((b_.x != c_.x) || (b_.y != c_.y)) && ((a_.x != c_.x) || (a_.y != c_.y)));
}

double Triangle::getArea() const
{
  return std::abs((((a_.x - c_.x) * (b_.y - c_.y)) - ((b_.x - c_.x) * (a_.y - c_.y))) * 0.5);
}

point_t Triangle::getCentre() const
{
  return point_t { (a_.x + b_.x + c_.x) / 3.0, (a_.y + b_.y + c_.y) / 3.0 };
}

rectangle_t Triangle::getFrameRect() const
{
  double maxX = std::max({ a_.x, b_.x, c_.x });
  double maxY = std::max({ a_.y, b_.y, c_.y });
  double minX = std::min({ a_.x, b_.x, c_.x });
  double minY = std::min({ a_.y, b_.y, c_.y });
  return rectangle_t { maxX - minX, maxY - minY, getCentre() };
}

void Triangle::move(double moveAbscissa, double moveOrdinate)
{
  a_.x += moveAbscissa;
  a_.y += moveOrdinate;
  b_.x += moveAbscissa;
  b_.y += moveOrdinate;
  c_.x += moveAbscissa;
  c_.y += moveOrdinate;
}

void Triangle::move(const point_t& point)
{
  move(point.x - getCentre().x, point.y - getCentre().y);
}
