#include "polygon.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

klimchuk::Polygon::Polygon(const std::initializer_list<point_t> points):
  size_{ points.size() },
  points_{ std::make_unique<point_t[]>(size_) }
{
  if (size_ < 3)
  {
    throw std::length_error("Polygon: Invalid initializer list to construct object");
  }
  size_t i = 0;
  for (point_t element : points)
  {
    points_[i] = element;
    ++i;
  }
  if (getArea() == 0.0)
  {
    throw std::invalid_argument("Polygot: Area of polygon should be more than zero");
  }
}

const klimchuk::point_t klimchuk::Polygon::operator[](size_t index) const
{
  if (index >= size_)
  {
    std::out_of_range("Polygon: Invalid index to access");
  }
  return points_[index];
}

klimchuk::point_t klimchuk::Polygon::operator[](size_t index)
{
  if (index >= size_)
  {
    std::out_of_range("Polygon: Invalid index to access");
  }
  return points_[index];
}

double klimchuk::Polygon::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_ - 1; ++i)
  {
    area += (points_[i].x * points_[i + 1].y) - (points_[i].y * points_[i + 1].x);
  }
  area += (points_[size_ - 1].x * points_[0].y) - (points_[size_ - 1].y * points_[0].x);
  return fabs(area) / 2;
}

klimchuk::rectangle_t klimchuk::Polygon::getFrameRect() const
{
  double minX = points_[0].x;
  double maxX = points_[0].x;
  double minY = points_[0].y;
  double maxY = points_[0].y;
  for (size_t i = 1; i < size_; ++i)
  {
    minX = std::min(minX, points_[i].x);
    maxX = std::max(maxX, points_[i].x);
    minY = std::min(minY, points_[i].y);
    maxY = std::max(maxY, points_[i].y);
  }
  point_t frameCenter;
  frameCenter.x = minX + ((maxX - minX) / 2);
  frameCenter.y = minY + ((maxY - minY) / 2);
  return rectangle_t{ maxX - minX, maxY - minY, frameCenter};
}

void klimchuk::Polygon::move(const point_t& point)
{
  point_t centreOfPolygon = getCentre();
  double moveAbscissa = point.x - centreOfPolygon.x;
  double moveOrdinate = point.y - centreOfPolygon.y;
  move(moveAbscissa, moveOrdinate);
}

void klimchuk::Polygon::move(double moveAbscissa, double moveOrdinate)
{
  for (size_t i = 0; i < size_; ++i)
  {
    points_[i].x += moveAbscissa;
    points_[i].y += moveOrdinate;
  }
}

void klimchuk::Polygon::scale(double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Polygon: Coefficient for scaling must be more, than zero");
  }
  point_t centreOfPolygon = getCentre();
  point_t resultOfScaling = { 0.0, 0.0 };
  for (size_t i = 0; i < size_; ++i)
  {
    resultOfScaling.x = (points_[i].x - centreOfPolygon.x) * coefficient;
    resultOfScaling.y = (points_[i].y - centreOfPolygon.y) * coefficient;
    points_[i] = resultOfScaling;
  }
}

klimchuk::point_t klimchuk::Polygon::getCentre() const
{
  point_t centreOfPolygon = { 0.0, 0.0 };
  for (size_t i = 0; i < size_; ++i)
  {
    centreOfPolygon.x += points_[i].x;
    centreOfPolygon.y += points_[i].y;
  }
  centreOfPolygon.x /= size_;
  centreOfPolygon.y /= size_;
  return centreOfPolygon;
}

void klimchuk::Polygon::rotate(double angle)
{
  angle *= M_PI / 180;
  double cosinusOfAngle = cos(angle);
  double sinusOfAngle = sin(angle);
  point_t centreOfPolygon = getCentre();
  point_t resultOfRotating = { 0.0, 0.0 };
  for (size_t i = 0; i < size_; ++i)
  {
    resultOfRotating.x = points_[i].x - centreOfPolygon.x;
    resultOfRotating.y = points_[i].y - centreOfPolygon.y;
    points_[i].x = resultOfRotating.x * cosinusOfAngle - resultOfRotating.y * sinusOfAngle + centreOfPolygon.x;
    points_[i].y = resultOfRotating.y * cosinusOfAngle + resultOfRotating.x * sinusOfAngle + centreOfPolygon.y;
  }
}

size_t klimchuk::Polygon::getSize() const
{
  return size_;
}
