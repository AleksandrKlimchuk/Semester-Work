#include "circle.hpp"
#include <cmath>
#include <stdexcept>

klimchuk::Circle::Circle(double posX, double posY, double radius):
  radius_{ radius },
  centre_{ posX, posY }
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Circle: Radius can't be less than a zero.");
  }
}

double klimchuk::Circle::getArea() const
{
  return  M_PI * radius_ * radius_;
}

klimchuk::rectangle_t klimchuk::Circle::getFrameRect() const
{
  return rectangle_t{ 2 * radius_, 2 * radius_, centre_ };
}

void klimchuk::Circle::move(const point_t& point)
{
  centre_ = point;
}

void klimchuk::Circle::move(double moveAbscissa, double moveOrdinate)
{
  centre_.x += moveAbscissa;
  centre_.y += moveOrdinate;
}

klimchuk::point_t klimchuk::Circle::getCentre() const
{
  return centre_;
}

void klimchuk::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Circle: Coefficient must be more than a zero.");
  }
  radius_ *= coefficient;
}

double klimchuk::Circle::getRadius() const
{
  return radius_;
}

void klimchuk::Circle::rotate(double)
{}
