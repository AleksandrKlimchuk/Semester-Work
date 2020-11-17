#include "triangle.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>

klimchuk::Triangle::Triangle(const point_t& firstTop, const point_t& secondTop, const point_t& thirdTop):
  a_{ firstTop },
  b_{ secondTop },
  c_{ thirdTop }
{
  double firstSide = sqrt(pow(secondTop.x - firstTop.x, 2) + pow(secondTop.y - firstTop.y, 2));
  double secondSide = sqrt(pow(thirdTop.x - secondTop.x, 2) + pow(thirdTop.y - secondTop.y, 2));
  double thirdSide = sqrt(pow(thirdTop.x - firstTop.x, 2) + pow(thirdTop.y - firstTop.y, 2));
  if ((firstSide + secondSide <= thirdSide) || (firstSide + thirdSide <= secondSide) || (secondSide + thirdSide <= firstSide))
  {
    throw std::invalid_argument("Triangle: Wrong value of coordinates.");
  }
}

double klimchuk::Triangle::getArea() const
{
  return std::abs((((a_.x - c_.x) * (b_.y - c_.y)) - ((b_.x - c_.x) * (a_.y - c_.y))) * 0.5);
}

klimchuk::point_t klimchuk::Triangle::getCentre() const
{
  return klimchuk::point_t { (a_.x + b_.x + c_.x) / 3.0, (a_.y + b_.y + c_.y) / 3.0 };
}

klimchuk::rectangle_t klimchuk::Triangle::getFrameRect() const
{
  double maxX = std::max({ a_.x, b_.x, c_.x });
  double maxY = std::max({ a_.y, b_.y, c_.y });
  double minX = std::min({ a_.x, b_.x, c_.x });
  double minY = std::min({ a_.y, b_.y, c_.y });
  return rectangle_t { maxX - minX, maxY - minY, getCentre() };
}

void klimchuk::Triangle::move(double moveAbscissa, double moveOrdinate)
{
  a_.x += moveAbscissa;
  a_.y += moveOrdinate;
  b_.x += moveAbscissa;
  b_.y += moveOrdinate;
  c_.x += moveAbscissa;
  c_.y += moveOrdinate;
}

void klimchuk::Triangle::move(const point_t& point)
{
  move(point.x - getCentre().x, point.y - getCentre().y);
}

void klimchuk::Triangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Triangle: Coefficient must be vore than a zero");
  }
  klimchuk::point_t centre = getCentre();
  a_.x = centre.x + (a_.x - centre.x) * coefficient;
  a_.y = centre.y + (a_.y - centre.y) * coefficient;
  b_.x = centre.x + (b_.x - centre.x) * coefficient;
  b_.y = centre.y + (b_.y - centre.y) * coefficient;
  c_.x = centre.x + (c_.x - centre.x) * coefficient;
  c_.y = centre.y + (c_.y - centre.y) * coefficient;
}

void klimchuk::Triangle::rotate(double angle)
{
  angle *= M_PI / 180;
  double cosinusOfAngle = cos(angle);
  double sinusOfAngle = sin(angle);
  klimchuk::point_t centre = getCentre();
  a_ = { centre.x + (cosinusOfAngle * (a_.x - centre.x)) - (sinusOfAngle * (a_.y - centre.y)),
      centre.y + (sinusOfAngle * (a_.x - centre.x)) + (cosinusOfAngle * (a_.y - centre.y)) };
  b_ = { centre.x + (cosinusOfAngle * (b_.x - centre.x)) - (sinusOfAngle * (b_.y - centre.y)),
      centre.y + (sinusOfAngle * (b_.x - centre.x)) + (cosinusOfAngle * (b_.y - centre.y)) };
  c_ = { centre.x + (cosinusOfAngle * (c_.x - centre.x)) - (sinusOfAngle * (c_.y - centre.y)),
      centre.y + (sinusOfAngle * (c_.x - centre.x)) + (cosinusOfAngle * (c_.y - centre.y)) };
}
