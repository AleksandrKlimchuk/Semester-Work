#include "composite-shape.hpp"
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include "shape.hpp"

klimchuk::CompositeShape::CompositeShape(const Shape::ShapePtr& shape) :
  size_{ 1 },
  arrayOfShapes_{ std::make_unique<ShapePtr[]>(size_) }
{
  if (!shape)
  {
    throw std::invalid_argument("CompositeShape: Parametr is not shape.");
  }
  arrayOfShapes_[0] = shape;
}

klimchuk::CompositeShape::CompositeShape(const CompositeShape& rhs) :
  size_{ rhs.size_ },
  arrayOfShapes_{ std::make_unique<Shape::ShapePtr[]>(size_) }
{
  for (size_t i = 0; i < size_; ++i)
  {
    arrayOfShapes_[i] = rhs.arrayOfShapes_[i];
  }
}

klimchuk::CompositeShape::CompositeShape(CompositeShape&& rhs) noexcept :
  size_{ rhs.size_ },
  arrayOfShapes_{ std::move(rhs.arrayOfShapes_) }
{}

klimchuk::CompositeShape& klimchuk::CompositeShape::operator=(const CompositeShape& rhs)
{
  if (this != &rhs)
  {
    arrayOfShapes_ = std::make_unique<Shape::ShapePtr[]>(rhs.size_);
    size_ = rhs.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      arrayOfShapes_[i] = rhs.arrayOfShapes_[i];
    }
  }
  return *this;
}

klimchuk::CompositeShape& klimchuk::CompositeShape::operator=(CompositeShape&& rhs) noexcept
{
  if (this != &rhs)
  {
    size_ = rhs.size_;
    arrayOfShapes_ = std::move(rhs.arrayOfShapes_);
  }
  return *this;
}

klimchuk::Shape::ShapePtr klimchuk::CompositeShape::operator[](size_t index)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape: Invalid index to access.");
  }
  return arrayOfShapes_[index];
}

klimchuk::Shape::ConstShapePtr klimchuk::CompositeShape::operator[](size_t index) const
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape: Invalid index to access.");
  }
  return arrayOfShapes_[index];
}

void klimchuk::CompositeShape::add(const Shape::ShapePtr& shape)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  if (!shape)
  {
    throw std::invalid_argument("CompositeShape: Parametr is not shape.");
  }
  std::unique_ptr<Shape::ShapePtr[]> tempArray = std::make_unique<Shape::ShapePtr[]>(size_ + 1);
  for (size_t i = 0; i < size_; ++i)
  {
    tempArray[i] = arrayOfShapes_[i];
  }
  tempArray[size_] = shape;
  ++size_;
  arrayOfShapes_.swap(tempArray);
}

void klimchuk::CompositeShape::remove(size_t index)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape: Invalid index to access.");
  }
  if (size_ == 1)
  {
    throw std::length_error("You can not delete last figure in CompositeShape.");
  }
  std::unique_ptr<Shape::ShapePtr[]> tempArray = std::make_unique<Shape::ShapePtr[]>(size_ - 1);
  for (size_t i = 0; i < index; ++i)
  {
    tempArray[i] = arrayOfShapes_[i];
  }
  for (size_t i = index; i < size_ - 1; ++i)
  {
    tempArray[i] = arrayOfShapes_[i + 1];
  }
  size_--;
  arrayOfShapes_.swap(tempArray);
}

size_t klimchuk::CompositeShape::getSize() const
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  return size_;
}

double klimchuk::CompositeShape::getArea() const
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  double sumOfAreas = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    sumOfAreas += arrayOfShapes_[i]->getArea();
  }
  return sumOfAreas;
}

klimchuk::rectangle_t klimchuk::CompositeShape::getFrameRect() const
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  rectangle_t rectangle(arrayOfShapes_[0]->getFrameRect());
  double topLine = rectangle.pos.y + (rectangle.height / 2);
  double bottomLine = topLine - rectangle.height;
  double rightLine = rectangle.pos.x + (rectangle.width / 2);
  double leftLine = rightLine - rectangle.width;
  for (size_t i = 1; i < size_; ++i)
  {
    rectangle = arrayOfShapes_[i]->getFrameRect();
    topLine = std::max(topLine, (rectangle.pos.y + (rectangle.height / 2)));
    bottomLine = std::min(bottomLine, (topLine - rectangle.height));
    rightLine = std::max(rightLine, (rectangle.pos.x + (rectangle.width / 2)));
    leftLine = std::min(leftLine, (rightLine - rectangle.width));
  }
  return rectangle_t{ (rightLine - leftLine), (topLine - bottomLine),
    {(leftLine + ((rightLine - leftLine) / 2)), (bottomLine + ((topLine - bottomLine) / 2))} };
}

klimchuk::point_t klimchuk::CompositeShape::getCentre() const
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  return getFrameRect().pos;
}

void klimchuk::CompositeShape::move(double moveAbscissa, double moveOrdinate)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  for (size_t i = 0; i < size_; ++i)
  {
    arrayOfShapes_[i]->move(moveAbscissa, moveOrdinate);
  }
}

void klimchuk::CompositeShape::move(const point_t& point)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  point_t oldCentre = getCentre();
  move((point.x - oldCentre.x), (point.y - oldCentre.y));
}

void klimchuk::CompositeShape::scale(double coefficient)
{
  if (!arrayOfShapes_)
  {
    throw std::domain_error("CompositeShape: Array of shapes is empty.");
  }
  if (coefficient <= 0)
  {
    throw std::invalid_argument("CompositeShape: Coefficient must be more than a zero.");
  }
  point_t centreOfComposite = getCentre();
  for (size_t i = 0; i < size_; ++i)
  {
    point_t centreOfShape = arrayOfShapes_[i]->getCentre();
    arrayOfShapes_[i]->move({ (centreOfComposite.x + (coefficient * (centreOfShape.x - centreOfComposite.x))),
      (centreOfComposite.y + (coefficient * (centreOfShape.y - centreOfComposite.y))) });
    arrayOfShapes_[i]->scale(coefficient);
  }
}

void klimchuk::CompositeShape::rotate(double angle)
{
  double cosinusOfAngle = cos(angle * M_PI / 180);
  double sinusOfAngle = sin(angle * M_PI / 180);
  point_t centreOFCompositeShape = getCentre();
  for (size_t i = 0; i < size_; ++i)
  {
    point_t centreOfShape = arrayOfShapes_[i]->getCentre();
    double newCentreAbscissa = centreOFCompositeShape.x + (cosinusOfAngle * (centreOfShape.x - centreOFCompositeShape.x)) 
      - (sinusOfAngle * (centreOfShape.y - centreOFCompositeShape.y));
    double newCentreOrdinate = centreOFCompositeShape.y + (cosinusOfAngle * (centreOfShape.y - centreOFCompositeShape.y))
      + (sinusOfAngle * (centreOfShape.x - centreOFCompositeShape.x));
    arrayOfShapes_[i]->move({ newCentreAbscissa, newCentreOrdinate });
    arrayOfShapes_[i]->rotate(angle);
  }
}
