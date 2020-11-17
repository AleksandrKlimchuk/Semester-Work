#include "rectangle.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>

klimchuk::Rectangle::Rectangle(double width, double height, double posX, double posY) :
  corners_ { point_t{ posX - (width / 2), posY + (height / 2) },
    point_t{ posX + (width / 2), posY + (height / 2) },
    point_t{ posX + (width / 2), posY - (height / 2) },
    point_t{ posX - (width / 2), posY - (height / 2)} }
{
  if (width <= 0)
  {
    throw std::invalid_argument("Rectangle: Wrong value of width");
  }
  if (height <= 0)
  {
    throw std::invalid_argument("Rectangle: Wrong value of height");
  }
}

double klimchuk::Rectangle::getArea() const
{
  return getHeight() * getWidth();
}

klimchuk::rectangle_t klimchuk::Rectangle::getFrameRect() const
{
  double minX = std::min({ corners_[0].x, corners_[1].x, corners_[2].x, corners_[3].x });
  double maxX = std::max({ corners_[0].x, corners_[1].x, corners_[2].x, corners_[3].x });
  double minY = std::min({ corners_[0].y, corners_[1].y, corners_[2].y, corners_[3].y });
  double maxY = std::max({ corners_[0].y, corners_[1].y, corners_[2].y, corners_[3].y });
  return rectangle_t{ maxX - minX, maxY - minY, klimchuk::point_t{ minX + ((maxX - minX) / 2), minY + ((maxY - minY) / 2)} };
}

void klimchuk::Rectangle::move(const klimchuk::point_t& point)
{
  point_t centre = getCentre();
  move(point.x - centre.x, point.y - centre.y);
}

void klimchuk::Rectangle::move(double moveAbscissa, double moveOrdinate)
{
  for (size_t i = 0; i < 4; ++i)
  {
    corners_[i].x += moveAbscissa;
    corners_[i].y += moveOrdinate;
  }
}

klimchuk::point_t klimchuk::Rectangle::getCentre() const
{
  return getFrameRect().pos;
}

void klimchuk::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Rectangle: Coefficient must be more, than a zero.");
  }
  double newWidth = getWidth() * coefficient;
  double newHeight = getHeight() * coefficient;
  point_t centre = getCentre();
  corners_[0] = point_t{ centre.x - (newWidth / 2), centre.y + (newHeight / 2) };
  corners_[1] = point_t{ centre.x + (newWidth / 2), centre.y + (newHeight / 2) };
  corners_[2] = point_t{ centre.x + (newWidth / 2), centre.y - (newHeight / 2) };
  corners_[3] = point_t{ centre.x - (newWidth / 2), centre.y - (newHeight / 2) };
}

double klimchuk::Rectangle::getHeight() const
{
  return sqrt(pow(corners_[1].x - corners_[2].x, 2) + pow(corners_[1].y - corners_[2].y, 2));
}

double klimchuk::Rectangle::getWidth() const
{
  return sqrt(((corners_[1].x - corners_[0].x) * (corners_[1].x - corners_[0].x))
    + ((corners_[1].y - corners_[0].y) * (corners_[1].y - corners_[0].y)));
}

void klimchuk::Rectangle::rotate(double angle)
{
  angle *= M_PI / 180;
  double cosinusOfAngle = cos(angle);
  double sinusOfAngle = sin(angle);
  point_t centre = getCentre();
  for (size_t i = 0; i < 4; ++i)
  {
    corners_[i] = { centre.x + (cosinusOfAngle * (corners_[i].x - centre.x)) - (sinusOfAngle * (corners_[i].y - centre.y)),
      centre.y + (sinusOfAngle * (corners_[i].x - centre.x)) + (cosinusOfAngle * (corners_[i].y - centre.y)) };
  }
}
