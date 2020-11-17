#include <iostream>
#include <stdexcept>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"

using namespace klimchuk;

int main()
{
  double width = 8.0, height = 4.2, abscissa = -9.0, ordinate = 7.2, radius = 5.0;
  point_t centreOfCircle{4.0, 5.2};
  Shape* rectangle = nullptr;
  try
  {
    rectangle = new Rectangle(width, height, abscissa, ordinate);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    delete rectangle;
    return 1;
  }

  Shape* circle = nullptr;
  try
  {
    circle = new Circle(centreOfCircle.x, centreOfCircle.y, radius);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    delete circle;
    delete rectangle;
    return 1;
  }
  std::cout << "The area of the circle is " << circle->getArea() << "\n"
      << "The centre of the rectangle is x: " << rectangle->getCentre().x 
      << " y: " << rectangle->getCentre().y << "\n"
      << "The centre of the circle is x: " << circle->getCentre().x 
      << " y: " << circle->getCentre().y << "\n";

  double movingX = 8.0;
  double movingY = 4.0;
  rectangle->move(movingX, movingY);

  std::cout << "The centre of the rectangle after moving is x: " << rectangle->getCentre().x << " y: "
      << rectangle->getCentre().y << "\n";

  centreOfCircle.x = 8.12;
  centreOfCircle.y = 3.91;
  circle->move(centreOfCircle);

  std::cout << "The centre of the circle  after moving is x: " << circle->getCentre().x << " y: "
      << circle->getCentre().y << "\n";

  try
  {
    rectangle->scale(0.5);
    std::cout << "Area of rectangle after scaling: " << rectangle->getArea() << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    delete rectangle;
    delete circle;
    return 1;
  }
  delete rectangle;

  try
  {
    circle->scale(5);
    std::cout << "Area of circle after scaling: " << circle->getArea() << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    delete circle;
    return 1;
  }
  delete circle;
  return 0;

}
