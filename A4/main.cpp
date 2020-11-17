#include <iostream>
#include <stdexcept>
#include <memory>
#include "../common/polygon.hpp"
#include "../common/matrix.hpp"
#include "../common/composite-shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"

using namespace klimchuk;

int main() 
{
  std::unique_ptr<Shape> shape = nullptr;
  double height = 7.0, width = 3.0;
  point_t centre{ 4.0, 12.0 };
  try
  {
    shape = std::make_unique<Rectangle>(height, width, centre.x, centre.y);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    shape.reset();
    return 1;
  }

  double movingAbscissa = 2.0, movingOrdinate = 10.0;
  point_t newCentre = { 3.0, 9.0 };
  shape->move(movingAbscissa, movingOrdinate);
  shape->move(newCentre);

  double coefficient = 12;
  try
  {
    shape->scale(coefficient);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    shape.reset();
    return 1;
  }

  double angle = 90.0;
  shape->rotate(angle);

  shape.reset();

  double radius = 13.0;
  point_t centreOfCircle = { 4.0, 2.0 };
  try
  {
    shape = std::make_unique<Circle>(centreOfCircle.x, centreOfCircle.y, radius);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    shape.reset();
    return 1;
  }
  movingAbscissa = 5.0, movingOrdinate = 7.0;
  newCentre = { 0.0, 2.0 };
  shape->move(movingAbscissa, movingOrdinate);
  shape->move(newCentre);

  coefficient = 5.0;
  try
  {
    shape->scale(coefficient);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    shape.reset();
    return 1;
  }

  shape->rotate(angle);

  shape.reset();

  std::unique_ptr<CompositeShape> compositeShape = nullptr;
  try
  {
    compositeShape = std::make_unique<CompositeShape>(std::make_shared<Circle>(centreOfCircle.x, centreOfCircle.y, radius));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    compositeShape.reset();
    return 1;
  }
  klimchuk::point_t a{ 0.0, 0.0 }, b{ 0.0, 4.0 }, c{ 7.0, 0.0 };
  try
  {
    compositeShape->add(std::make_shared<Rectangle>(height, width, centre.x, centre.y));
    compositeShape->add(std::make_shared<Triangle>(a, b, c));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    compositeShape.reset();
    return 1;
  }
  
  compositeShape->move(newCentre);
  compositeShape->move({ movingAbscissa, movingOrdinate });
  compositeShape->getFrameRect();
  compositeShape->getCentre();
  compositeShape->getArea();
  try
  {
    compositeShape->scale(coefficient);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    compositeShape.reset();
    return 1;
  }

  compositeShape->rotate(angle);
  compositeShape.reset();

  std::unique_ptr<Matrix> matrix{ nullptr };
  matrix = std::make_unique<Matrix>();
  try
  {
    matrix->add(std::make_shared<Circle>(centreOfCircle.x, centreOfCircle.y, radius));
    matrix->add(std::make_shared<Rectangle>(height, width, centre.x, centre.y));
    matrix->add(std::make_shared<Triangle>(a, b, c));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    matrix.reset();
    return 1;
  }
  try
  {
    CompositeShape compositeShape1(std::make_shared<Circle>(1, 2, 10));
    compositeShape1.add(std::make_shared<Rectangle>(1, 3, 4, 6));
    std::shared_ptr<Shape> compositeShapeForAdd = std::make_shared<CompositeShape>(compositeShape1);
    matrix->add(compositeShapeForAdd);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    matrix.reset();
    return 1;
  }
  matrix.reset();

  std::unique_ptr<Polygon> polygon{ nullptr };
  std::initializer_list<point_t> points = { { 1, 1 }, { 3, 1 }, { 3, 3 }, { 1, 3 } };
  try
  {
    polygon = std::make_unique<Polygon>(points);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    polygon.reset();
    return 1;
  }
  newCentre = { 3.0, 2.0 };
  polygon->move(newCentre);
  polygon->move(10.0, 2.0);

  coefficient = 2;
  try
  {
    polygon->scale(coefficient);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    polygon.reset();
    return 1;
  }

  polygon->rotate(angle);
  polygon.reset();

  return 0;
}
