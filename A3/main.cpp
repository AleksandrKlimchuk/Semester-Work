#include <iostream>
#include <stdexcept>
#include <memory>
#include "../common/composite-shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"

using namespace klimchuk;

int main() 
{
  Shape* shape = nullptr;
  double height = 7.0, width = 3.0;
  point_t centre{4.0, 12.0};
  try
  {
    shape = new Rectangle(height, width, centre.x, centre.y);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    delete shape;
    return 1;
  }

  double movingAbscissa = 2.0, movingOrdinate = 10.0;
  point_t newCentre = {3.0, 9.0};
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
    delete shape;
    return 1;
  }
  delete shape;

  double radius = 13.0;
  point_t centreOfCircle = {4.0, 2.0};
  try
  {
    shape = new Circle(centreOfCircle.x, centreOfCircle.y, radius);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    delete shape;
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
    delete shape;
    return 1;
  }
  delete shape;

  klimchuk::point_t a{ 0.0, 0.0 }, b{ 0.0, 4.0 }, c{ 7.0, 0.0 };

  std::unique_ptr<CompositeShape> compositeShape = nullptr;
  try
  {
    compositeShape = std::make_unique<CompositeShape>(std::make_shared<Circle>(centreOfCircle.x, centreOfCircle.y, radius));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  try
  {
    compositeShape->add(std::make_shared<Rectangle>(height, width, centre.x, centre.y));
    compositeShape->add(std::make_shared<Triangle>(a, b, c));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  
  compositeShape->move(newCentre);
  compositeShape->move({ movingAbscissa, movingOrdinate });
  compositeShape->getFrameRect();
  compositeShape->getCentre();
  compositeShape->getArea();
  try
  {
    compositeShape->scale(10);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }

  return 0;
}
